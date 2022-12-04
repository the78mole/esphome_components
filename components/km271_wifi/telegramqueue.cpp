#include "telegramqueue.h"
#include "esphome/core/log.h"
#include <string.h>

namespace esphome {
namespace KM271 {

static const char * TAG = "TelegramQueue";

TelegramQueue::TelegramQueue():
    currentQueueLength(0),
    currentQueueOffset(0)
{

}

bool TelegramQueue::enqueueTelegram(const uint8_t *data, uint8_t length)
{
    ESP_LOGD(TAG, "Enqueuing telegram of length %d ql %d qo %d", length, currentQueueLength, currentQueueOffset);

    if(currentQueueLength + currentQueueOffset + length + sizeof (length) > QUEUE_SIZE) {
        compact();
        if (remainingCapacity() < length + sizeof (length)) {
            ESP_LOGE(TAG, "Telegram queue is full ql %d qo %d", currentQueueLength, currentQueueOffset);
            return false;
        }
    }

    queue[currentQueueLength + currentQueueOffset] = length;
    currentQueueLength ++;
    memcpy(&queue[currentQueueLength + currentQueueOffset], data, length);
    currentQueueLength += length;

    return true;
}

uint8_t TelegramQueue::popTelegram(uint8_t *dest, uint8_t maxSize)
{
    if(isEmpty()) {
        return 0;
    }
    uint8_t result;

    uint8_t telegramLength = queue[currentQueueOffset];
    currentQueueOffset += 1;
    currentQueueLength -= 1;

    if (telegramLength <= maxSize) {
        if (currentQueueOffset + telegramLength > QUEUE_SIZE) {
            ESP_LOGE(TAG, "Internal error: queue sizes do not match %d + %d > %d, resetting", currentQueueOffset, telegramLength, maxSize);
            currentQueueLength = 0;
            currentQueueOffset = 0;
            return 0;
        }

        memcpy(dest, &queue[currentQueueOffset], telegramLength);
        result = telegramLength;
    } else {
        ESP_LOGE(TAG, "Telegram to large to pop: %d > %d", telegramLength, maxSize);
        result = 0;
    }

    currentQueueLength -= telegramLength;
    if (currentQueueLength <= 0) {
        currentQueueOffset = 0;
    } else {
        currentQueueOffset += telegramLength;
    }
    ESP_LOGD(TAG, "After pop ql %d qo %d", currentQueueLength, currentQueueOffset);

    return result;
}


bool TelegramQueue::isEmpty() const
{
    return currentQueueLength == 0;
}

uint16_t TelegramQueue::remainingCapacity() const
{
    return(QUEUE_SIZE - currentQueueLength);
}

void TelegramQueue::compact()
{
    if (currentQueueOffset > 0) {
        memmove(queue, &queue[currentQueueOffset], currentQueueLength);
        currentQueueOffset = 0;
    }
    ESP_LOGD(TAG, "After compacting ql %d qo %d", currentQueueLength, currentQueueOffset);
}

/** the following to functions contain test code for the telegram queue. comment it in and call it to check
 * that the queue works as expected */
/*
void check(bool confition, const char *message)
{
    if (!confition) {
        ESP_LOGD(TAG, "=> Condition check failed: %s", message);

    }
}

void testTelegramQueue()
{
   {
        const uint8_t sampleTelegram[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        uint8_t sampleTelegramLength = 9;
        uint8_t buf[9];

        TelegramQueue tq;
        check(tq.isEmpty(), "empty");

        bool result;
        result = tq.enqueueTelegram(sampleTelegram, sampleTelegramLength);
        check(result, "enq 1");
        result = tq.enqueueTelegram(sampleTelegram, sampleTelegramLength);
        check(result, "enq 2");
        result = tq.enqueueTelegram(sampleTelegram, sampleTelegramLength);
        check(result, "enq 3");

        check(!tq.isEmpty(), "not empty");

        uint8_t len;
        len = tq.popTelegram(buf, 9);
        check(len == 9, "pop 1 len");
        check(!tq.isEmpty(), "not empty 2");

        len = tq.popTelegram(buf, 9);
        check(len == 9, "pop 2 len");
        check(!tq.isEmpty(), "not empty 3");

        len = tq.popTelegram(buf, 9);
        check(len == 9, "pop 3 len");
        check(tq.isEmpty(), "empty 2");

        len = tq.popTelegram(buf, 9);
        check(buf[1] == 2, "buf contents 2");
        check(buf[8] == 9, "buf contents 9");
        check(len == 0, "pop empty len");

        result = tq.enqueueTelegram(sampleTelegram, sampleTelegramLength);
        check(result, "enq 4");
        for(int i=0; i<30; i++) {
            result = tq.enqueueTelegram(sampleTelegram, sampleTelegramLength);
            check(result, "enq loop");
            len = tq.popTelegram(buf, 9);
            check(len == 9, "pop loop");
            check(!tq.isEmpty(), "not empty loop");
            check(buf[1] == 2, "buf contents loop 2");
            check(buf[8] == 9, "buf contents loop 9");
        }

        len = tq.popTelegram(buf, 9);
        check(len == 9, "pop after loop");
        check(tq.isEmpty(), "empty after loop");
    }
}
*/
}
}
