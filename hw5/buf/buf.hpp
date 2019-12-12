#pragma once

#include <vector>


class BitsWriter {
  public:
    void write_bit(bool bit);
    void write_byte(unsigned char byte);

    std::vector<unsigned char> get_result();

  private:
    std::vector<unsigned char> buffer_;
    unsigned char accumulator_ = 0;
    size_t bits_count_ = 0;
};


class BitsReader {
  public:
    bool read_bit(const std::vector<unsigned char>& buffer);
    unsigned char read_byte(const std::vector<unsigned char>& buffer);
    bool is_end_position(const std::vector<unsigned char>& buffer) const;
    
  private:
    size_t position_ = 0;
    size_t bits_count_ = 0;
    unsigned char state_ = 0;
};
