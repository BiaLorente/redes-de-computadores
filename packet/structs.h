struct
{
    int seqNum;
    int armed;
    int finished;
    char *buffer;
    //Timing object here
} typedef sentFrame;

struct
{
    int16_t sourceAddress;
    int16_t destAddress;
    int16_t length;
    int16_t checksum;
    char data[4];
    sentFrame frame;
} typedef packet;
