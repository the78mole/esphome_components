#include "3964r.h"
#include "km271_helpers.h"
#include "esphome/core/log.h"
#include <string.h>

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

Writer3964R::Writer3964R():
    writerState(Idle),
    retryCount(0)
{

}

void Writer3964R::telegramFinished()
{
    hasUnhandledDLE = false;
    bytesSent = 0;
    telegramLength = 0;
    writerState = Idle;
    retryCount = 0;

    if (!queue.isEmpty()) {
        telegramLength = queue.popTelegram(telegramToSend, MAX_TELEGRAM_SIZE);
        if (telegramLength >0) {
            writerState = RequestPending;
        }
    }
}

bool Writer3964R::enqueueTelegram(const uint8_t *data, uint8_t length)
{
    if (length > MAX_TELEGRAM_SIZE) {
        ESP_LOGE(TAG, "Telegram too long %d", length);
        return false;
    }

    log_hex_buffer("Sending Telegram", data, length);

    if(writerState != Idle) {
        return queue.enqueueTelegram(data, length);
    }

    hasUnhandledDLE = false;
    bytesSent = 0;

    memcpy(telegramToSend, data, length);
    telegramLength = length;
    writerState = RequestPending;
    retryCount = 0;
    return true;
}

void Writer3964R::setSTXSent()
{
    writerState = WaitingForDle;
    ESP_LOGD(TAG, "stx sent, waiting for dle");
}

uint8_t Writer3964R::popNextByte()
{
    if (writerState == Idle ||  writerState == RequestPending) {
        ESP_LOGE(TAG, "Invalid state for pop: %d", writerState);
        return 0;
    }
    if(writerState == WaitingForDle) {
        //ESP_LOGD(TAG, "Starting to send");
        currentChecksum = 0;
        writerState = Sending;
    }

    if (writerState == Sending) {
         if (bytesSent >= telegramLength) {
            ESP_LOGE(TAG, "too many bytes sent");
            return 0;
        }

        uint8_t c = telegramToSend[bytesSent];
        if (c == DLE) {
            if (hasUnhandledDLE) {
                hasUnhandledDLE = false;
            } else {
                hasUnhandledDLE = true;
                ESP_LOGD(TAG, "Sending escaped DLE");
                currentChecksum ^= DLE;
                return DLE;
            }
        }
        bytesSent ++;
        if (bytesSent >= telegramLength) {
            writerState = SendingDLE;
        }
        currentChecksum ^= c;
        //ESP_LOGD(TAG, "Sb %02X.", c);
        return c;
    } else if(writerState == SendingDLE) {
        //ESP_LOGD(TAG, "S DLE.");
        currentChecksum ^= DLE;
        writerState = SendingETX;
        return DLE;
    } else if (writerState == SendingETX) {
        //ESP_LOGD(TAG, "S ETX.");
        writerState = SendingChecksum;
        currentChecksum ^= ETX;
        return ETX;
    } else if (writerState == SendingChecksum) {
        writerState = WaitForAck;
        // ESP_LOGD(TAG, "SCS %02X", currentChecksum);
        return currentChecksum;
    }

    ESP_LOGE(TAG, "Invalid state %d", writerState);
    return 0;
}

bool Writer3964R::hasByteToSend()
{
    return writerState==WaitingForDle || writerState == Sending || writerState == SendingDLE || writerState == SendingETX || writerState == SendingChecksum;
}

void Writer3964R::restartTelegram()
{
    if(writerState == WaitForAck || writerState == WaitingForDle || writerState == RequestPending) {
        writerState = RequestPending;
        bytesSent = 0;
        currentChecksum = 0;
        retryCount ++;
    } else {
        ESP_LOGE(TAG, "Can't restart: invalid state %d", writerState);
    }
}

}
}
