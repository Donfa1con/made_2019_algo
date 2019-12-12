#include "buf.hpp"

#include <iostream>
#include <vector>


void BitsWriter::write_bit(bool bit) {
  accumulator_ |= static_cast<unsigned char>(bit) << bits_count_;
  ++bits_count_;
  if (bits_count_ == 8) {
    bits_count_ = 0;
    buffer_.push_back(accumulator_);
    accumulator_ = 0;
  }
}


void BitsWriter::write_byte(unsigned char byte) {
  if (bits_count_ == 0) {
    buffer_.push_back(byte);
  } else {
    accumulator_ |= byte << bits_count_;
    buffer_.push_back(accumulator_);
    accumulator_ = byte >> (8 - bits_count_);
  }
}


std::vector<unsigned char> BitsWriter::get_result() {
  if (bits_count_ != 0) {
    buffer_.push_back(accumulator_);
  }
  buffer_.push_back(static_cast<unsigned char>(bits_count_));
  return std::move(buffer_);
}


bool BitsReader::read_bit(const std::vector<unsigned char>& buffer) {
    if (bits_count_ % 8 == 0) {
        bits_count_ = 1;
        state_ = buffer[position_++];
        return state_ & 1;
    } else {
        return (state_ >> bits_count_++) & 1;
    }
}


unsigned char BitsReader::read_byte(const std::vector<unsigned char>& buffer) {
    if (bits_count_ % 8 == 0) {
        return buffer[position_++];
    } else {
        unsigned char old_state = state_;
        state_ = buffer[position_++];
        return (old_state >> bits_count_) | state_ << (8 - bits_count_);
    }
}


bool BitsReader::is_end_position(const std::vector<unsigned char>& buffer) const {
    auto last_count = buffer.back();
    if (last_count == 0) {
        last_count = 8;
    }
    return position_ * 8 + bits_count_ < (buffer.size() - 1) * 8 + last_count;
}
