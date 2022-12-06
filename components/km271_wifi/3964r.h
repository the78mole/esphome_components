#ifndef C3964R_H
#define C3964R_H

#include <stdint.h>
#include "telegramqueue.h"

#define MAX_TELEGRAM_SIZE 64

namespace esphome {
namespace KM271 {

static const char STX = 0x02;
static const char ETX = 0x03;
static const char DLE = 0x10;
static const char NAK = 0x15;

static const uint32_t QVZ = 2000;   // Quittierungsverzugszeit: Time-out in milliseconds for achnowledge
static const uint32_t ZVZ = 220;    // Zeichenverzugszeit: Time-out between data of active transmission

static const uint8_t maxTelegramRetries = 5; // stop if no ack after this amount of tries

enum ParserState {
    WaitingForStart,
    WaitingForEtx,
    WaitingForChecksum,
    TelegramComplete,
    ParseError
};


class Parser3964R
{
public:
    Parser3964R();

    void reset();
    void startTelegram();
    void consumeByte(uint8_t byte);
    bool parsingInProgress();


public:
    uint8_t decodedTelegram[MAX_TELEGRAM_SIZE];
    ParserState parserState;
    uint16_t currentTelegramLength;

private:
    bool hasUnhandledDLE;
    uint8_t currentChecksum;

};

enum WriterState {
    Idle,
    RequestPending,
    WaitingForDle,
    Sending,
    SendingDLE,
    SendingETX,
    SendingChecksum,
    WaitForAck
};

class Writer3964R
{
public:
    Writer3964R();
    bool enqueueTelegram(const uint8_t *data, uint8_t length);
    void telegramFinished();

    void setSTXSent();
    uint8_t popNextByte();
    bool hasByteToSend();
    void restartTelegram();

public:
    WriterState writerState;
    uint8_t retryCount;


private:
    uint8_t telegramToSend[MAX_TELEGRAM_SIZE];
    uint16_t telegramLength;
    bool hasUnhandledDLE;
    uint8_t currentChecksum;
    uint16_t bytesSent;
    TelegramQueue queue;

};

}
}

#endif // C3964R_H
