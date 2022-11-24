#include "3964r.h"
#include "esphome/core/log.h"


namespace esphome {
namespace KM271 {

static const char *const TAG = "km271";

Parser3964R::Parser3964R():
    parserState(WaitingForStart),
    currentTelegramLength(0),
    hasUnhandledDLE(false)
{

}


void Parser3964R::reset()
{
    parserState = WaitingForStart;
    currentTelegramLength = 0;
    hasUnhandledDLE = false;
    currentChecksum = 0;
}


void Parser3964R::startTelegram()
{
    currentTelegramLength = 0;
    hasUnhandledDLE = false;
    parserState = WaitingForEtx;
    currentChecksum = 0;
}


void Parser3964R::consumeByte(uint8_t byte)
{
    if (parserState == WaitingForEtx) {
        if(currentTelegramLength >= MAX_TELEGRAM_SIZE) {
            ESP_LOGE(TAG, "RX Buffer overrun!");
            parserState = ParseError;
            return;
        }

        currentChecksum ^= byte;

        if(byte == DLE) {
            if(!hasUnhandledDLE) {
                hasUnhandledDLE = true;
                return;
            } else {
                hasUnhandledDLE = false;
            }
        } else if (byte == ETX) {
            if (hasUnhandledDLE) {
                parserState = WaitingForChecksum;
                hasUnhandledDLE = false;
                return;
            }
        } else {
            if (hasUnhandledDLE) {
                // log error
                parserState = ParseError;
            }
        }

        decodedTelegram[currentTelegramLength] = byte;
        currentTelegramLength += 1;
    } else if (parserState == WaitingForChecksum) {
        if (byte == currentChecksum) {
            // good
            parserState = TelegramComplete;
        } else {
            parserState = ParseError;
            // bad
        }

    } else {
        // log error: invalid state
        return;

    }


}

bool Parser3964R::parsingInProgress()
{
    return parserState == WaitingForEtx || parserState == WaitingForChecksum;
}

}
}
