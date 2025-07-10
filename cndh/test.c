



void convert_packet_1f1f_to_1f(uint8_t *data, uint16_t payload_size)
{
    uint16_t write_idx = 5; // Start writing after ESC, SOM, ID, SRC, DST
    uint16_t read_idx = 5;  // Start reading after ESC, SOM, ID, SRC, DST

    while (read_idx < payload_size + 5) {
        if (data[read_idx] == ESC && data[read_idx + 1] == ESC) {
            data[write_idx++] = ESC;
            read_idx += 2;
        } else {
            data[write_idx++] = data[read_idx++];
        }
    }
}