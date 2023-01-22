#ifndef KM271_COMMUNICATION_COMPONENTS_H
#define KM271_COMMUNICATION_COMPONENTS_H

#include "km271_params.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace KM271 {

class Writer3964R;

class CommunicationComponent
{
public:
    CommunicationComponent(bool writable);
    void setupWriting(Writer3964R * writer, TransmissionParameter transmissionParameter);

    virtual void handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value);
    virtual void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value);
    virtual void handleReceivedFloatValue(uint16_t sensorTypeParam, float value);
    virtual void loop() {}

    bool isWritable() const;

protected:
    bool writable;
    Writer3964R * writer;
    TransmissionParameter transmissionParameter;
};

class BuderusParamSwitch: public esphome::switch_::Switch, public CommunicationComponent {
public:
    BuderusParamSwitch();
    void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value) override;

protected:
    void write_state(bool state) override;

};

class BuderusParamNumber: public esphome::number::Number, public CommunicationComponent {
public:
    BuderusParamNumber();
    void loop() override;
    void handleReceivedSignedValue(uint16_t sensorTypeParam, int32_t value) override;
    void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value) override;
    void handleReceivedFloatValue(uint16_t sensorTypeParam, float value) override;

protected:
    void control(float value);

private:
    void sendAndConfirm(const uint8_t * message, uint8_t messageLength, float valueToConfirm);
    void buildTelegramSendAndConfirm(uint8_t telegramDataType, uint8_t telegramOffset, uint8_t telegramValuePosition, uint8_t telegramValue, float valueToConfirm);
private:

    uint32_t lastWriteRequest;
    bool hasPendingWriteRequest;
    float pendingWriteValue;
};

class BuderusParamSelect: public esphome::select::Select, public CommunicationComponent {
public:
    BuderusParamSelect();
    void setSelectMappings(std::vector<uint8_t> mappings);
    void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value) override;

protected:
    void control(const std::string &value) override;

private:
    void sendAndConfirm(const uint8_t *message, uint8_t messageLength, const std::string &value);
    void buildTelegramSendAndConfirm(uint8_t telegramDataType, uint8_t telegramOffset, uint8_t telegramValuePosition, uint8_t selectIndex, const std::string &value);

private:
    std::vector<uint8_t> mappings; // this stores the number to read/write for each select option
};


class FirmwareVersionSensor: public esphome::text_sensor::TextSensor, public CommunicationComponent {
public:
    FirmwareVersionSensor();
    void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value) override;

private:
    uint8_t major;
    bool major_known;
    uint8_t minor;
    bool minor_known;
};


/** Helper class to reassemble values that span multiple buderus parameters */
class MultiParameterUnsignedIntegerAssembler: public CommunicationComponent
{
public:

    MultiParameterUnsignedIntegerAssembler(esphome::sensor::Sensor *targetSensor);
    void handleReceivedUnsignedValue(uint16_t sensorTypeParam, uint32_t value) override;
private:
    esphome::sensor::Sensor * sensor;
    uint8_t components[3];
    bool component_known[3];
};


}
}

#endif // KM271_COMMUNICATION_COMPONENTS_H
