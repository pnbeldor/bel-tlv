/* --- AdvancedTLV.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 11/20/2025
------------------------------------------ */
#ifndef __ADVANCED_TLV_H__
#define __ADVANCED_TLV_H__

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class AdvancedTLV {
public:
    enum Type : uint16_t {
        INTEGER = 1,
        STRING = 2,
        BOOLEAN = 3,
        ARRAY = 4,
        NESTED = 5
    };

private:
    Type type_;
    std::vector<uint8_t> value_;
    std::vector<std::unique_ptr<AdvancedTLV>> children_;

public:
    AdvancedTLV(Type type);
    AdvancedTLV(Type type, const std::vector<uint8_t>& value);
    
    // Factory methods
    static std::unique_ptr<AdvancedTLV> CreateInteger(int32_t value) {
        auto tlv = std::make_unique<AdvancedTLV>(INTEGER);
        tlv->SetInteger(value);
        return tlv;
    }
    
    static std::unique_ptr<AdvancedTLV> CreateString(const std::string& value) {
        auto tlv = std::make_unique<AdvancedTLV>(STRING);
        tlv->SetString(value);
        return tlv;
    }
    
    static std::unique_ptr<AdvancedTLV> CreateBoolean(bool value) {
        auto tlv = std::make_unique<AdvancedTLV>(BOOLEAN);
        tlv->SetBoolean(value);
        return tlv;
    }
    
    static std::unique_ptr<AdvancedTLV> CreateArray() {
        return std::make_unique<AdvancedTLV>(ARRAY);
    }
    
    static std::unique_ptr<AdvancedTLV> CreateNested() {
        return std::make_unique<AdvancedTLV>(NESTED);
    }
    
    // Value setters
    void SetInteger(int32_t value) {
        value_.clear();
        for (int i = sizeof(int32_t) - 1; i >= 0; --i) {
            value_.push_back((value >> (i * 8)) & 0xFF);
        }
    }
    
    void SetString(const std::string& value) {
        value_.assign(value.begin(), value.end());
    }
    
    void SetBoolean(bool value) {
        value_.clear();
        value_.push_back(value ? 1 : 0);
    }
    
    // Children management
    void AddChild(std::unique_ptr<AdvancedTLV> child) {
        children_.push_back(std::move(child));
    }
    
    // Serialization
    std::vector<uint8_t> Serialize() const {
        std::vector<uint8_t> result;
        
        // Serialize type
        result.push_back((type_ >> 8) & 0xFF);
        result.push_back(type_ & 0xFF);
        
        // For nested types, serialize children first
        std::vector<uint8_t> value_data;
        if (type_ == ARRAY || type_ == NESTED) {
            for (const auto& child : children_) {
                auto child_data = child->Serialize();
                value_data.insert(value_data.end(), child_data.begin(), child_data.end());
            }
        } else {
            value_data = value_;
        }
        
        // Serialize length
        uint16_t length = value_data.size();
        result.push_back((length >> 8) & 0xFF);
        result.push_back(length & 0xFF);
        
        // Serialize value
        result.insert(result.end(), value_data.begin(), value_data.end());
        
        return result;
    }
    
    // Getters
    Type GetType() const { return type_; }
    const std::vector<uint8_t>& GetValue() const { return value_; }
    const std::vector<std::unique_ptr<AdvancedTLV>>& GetChildren() const { return children_; }
    
    // Value converters
    int32_t AsInteger() const {
        if (value_.size() != sizeof(int32_t)) {
            throw std::runtime_error("Invalid integer size");
        }
        int32_t result = 0;
        for (uint8_t byte : value_) {
            result = (result << 8) | byte;
        }
        return result;
    }
    
    std::string AsString() const
    {
        return std::string(value_.begin(), value_.end());
    }
    
    bool AsBoolean() const
    {
        return !value_.empty() && value_[0] != 0;
    }
};

#endif // __ADVANCED_TLV_H__
