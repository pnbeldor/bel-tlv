/* --- TLVUtils.h --- */

/* ------------------------------------------
Author: Pnbeldor
Date: 11/20/2025
------------------------------------------ */

#ifndef TLVUTILS_H
#define TLVUTILS_H

// Helper functions for working with TLV
class TLVUtils {
public:
    static void printTLV(const std::vector<uint8_t>& data) {
        size_t offset = 0;
        int index = 0;
        
        while (offset < data.size()) {
            try {
                auto tlv = TLVParser::Parse(data, offset);
                std::cout << "TLV " << index++ << ": Type=" << tlv->GetType() 
                         << ", Length=" << tlv->GetValue().size() << std::endl;
                
                // Print value based on type
                switch (tlv->GetType()) {
                    case TLV::INTEGER:
                        std::cout << "  Value (int): " << tlv->AsInteger() << std::endl;
                        break;
                    case TLV::STRING:
                        std::cout << "  Value (str): " << tlv->AsString() << std::endl;
                        break;
                    case TLV::BOOLEAN:
                        std::cout << "  Value (bool): " << (tlv->AsBoolean() ? "true" : "false") << std::endl;
                        break;
                    default:
                        std::cout << "  Value (raw): ";
                        for (uint8_t byte : tlv->GetValue()) {
                            printf("%02X ", byte);
                        }
                        std::cout << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error parsing TLV at offset " << offset << ": " << e.what() << std::endl;
                break;
            }
        }
    }
    
    static std::vector<uint8_t> createMessage(const std::vector<std::unique_ptr<TLV>>& tlvs) {
        std::vector<uint8_t> result;
        for (const auto& tlv : tlvs) {
            auto data = tlv->Serialize();
            result.insert(result.end(), data.begin(), data.end());
        }
        return result;
    }
};
#endif // TLVUTILS_H
