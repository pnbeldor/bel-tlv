#include <iostream>

#include "TLV.h"
#include "TLVParser.h"
#include "AdvancedTLV.h"

void basicExample() {
    std::cout << "=== Basic TLV Example ===" << std::endl;
    
    // Create TLV objects
    auto integer_tlv = TLV::CreateInteger(42);
    auto string_tlv = TLV::CreateString("Hello, TLV! Hello, TLV!Hello, TLV! Hello, TLV! Hello, TLV! Hello, TLV! Hello, TLV!Hello, TLV! Hello, TLV! Hello, TLV! Hello, TLV! Hello, TLV!Hello, TLV! Hello, TLV! Hello, TLV!");
    auto bool_tlv = TLV::CreateBool(true);
    
    // Serialize
    auto integer_data = integer_tlv->Serialize();
    auto string_data = string_tlv->Serialize();
    auto bool_data = bool_tlv->Serialize();
    
    std::cout << "Integer TLV size: " << integer_data.size() << " bytes" << std::endl;
    std::cout << "String TLV size: " << string_data.size() << " bytes" << std::endl;
    std::cout << "Boolean TLV size: " << bool_data.size() << " bytes" << std::endl;
}

void advancedExample() {
    std::cout << "\n=== Advanced TLV Example ===" << std::endl;
    
    // Create a nested structure
    auto person = AdvancedTLV::CreateNested();
    
    auto name = AdvancedTLV::CreateString("Pierre Nicolson Beldor, Pierre-Nicolson Michael II Beldor");
    auto age = AdvancedTLV::CreateInteger(30);
    auto isStudent = AdvancedTLV::CreateBoolean(false);
    
    person->AddChild(std::move(name));
    person->AddChild(std::move(age));
    person->AddChild(std::move(isStudent));
    
    // Serialize the nested structure
    auto serialized = person->Serialize();
    std::cout << "Nested TLV size: " << serialized.size() << " bytes" << std::endl;
    
    // Print hex representation
    std::cout << "Hex: ";
    for (uint8_t byte : serialized) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
}

void arrayExample() {
    std::cout << "\n=== Array TLV Example ===" << std::endl;
    
    auto numbers = AdvancedTLV::CreateArray();
    
    for (int i = 1; i <= 8; ++i) {
        numbers->AddChild(AdvancedTLV::CreateInteger(i * 10));
    }
    
    auto serialized = numbers->Serialize();
    std::cout << "Array TLV size: " << serialized.size() << " bytes" << std::endl;
}

void parsingExample() {
    std::cout << "\n=== Parsing Example ===" << std::endl;
    
    // Create and serialize a TLV
    std::string msg = "Test Message";
    TLV original(Type::STRING, msg);
    auto data = original.Serialize();

    std::cout << "Original string value: \"Test Message\"" << std::endl;
    std::cout << "Serialized data (" << data.size() << " bytes): ";

    // Print hex representation
    std::cout << "Hex: ";
    for (uint8_t byte : data) {
        printf("%02X ", byte);
    }
    std::cout << std::endl;
    
    // Parse it back
    size_t offset = 0;
    try {
        auto parsed = TLVParser::Parse(data, offset);
        std::cout << "Parsed type: " << (int)(parsed->GetType()) << std::endl;
        std::cout << "Parsed value: " << parsed->AsString() << std::endl;
        std::cout << "Parsed value length: " << parsed->GetValue().size() << " bytes" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
    }
}

int main() {
    basicExample();
    advancedExample();
    arrayExample();
    parsingExample();
    
    return 0;
}