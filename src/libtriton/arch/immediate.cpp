//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <cpuSize.hpp>
#include <exceptions.hpp>
#include <immediate.hpp>



namespace triton {
  namespace arch {

    Immediate::Immediate() {
      this->value = 0;
    }


    Immediate::Immediate(triton::uint64 value, triton::uint32 size /* bytes */) {
      if (size == 0)
        throw triton::exceptions::Immediate("Immediate::Immediate(): size cannot be zero.");

      if (size != BYTE_SIZE && size != WORD_SIZE && size != DWORD_SIZE && size != QWORD_SIZE && size != DQWORD_SIZE && size != QQWORD_SIZE && size != DQQWORD_SIZE)
        throw triton::exceptions::Immediate("Immediate::Immediate(): size must be aligned.");

      switch (size) {
        case BYTE_SIZE:
          this->value = static_cast<triton::uint8>(value);
          break;
        case WORD_SIZE:
          this->value = static_cast<triton::uint16>(value);
          break;
        case DWORD_SIZE:
          this->value = static_cast<triton::uint32>(value);
          break;
        default:
          this->value = value;
      }

      this->setPair(std::make_pair(((size * BYTE_SIZE_BIT) - 1), 0));
    }


    Immediate::Immediate(const Immediate& other) : BitsVector(other) {
      this->copy(other);
    }


    Immediate::~Immediate() {
    }


    triton::uint64 Immediate::getValue(void) const {
      return this->value;
    }


    void Immediate::setValue(triton::uint64 v) {
      this->value = v;
    }


    triton::uint32 Immediate::getAbstractLow(void) const {
      return this->getLow();
    }


    triton::uint32 Immediate::getAbstractHigh(void) const {
      return this->getHigh();
    }


    triton::uint32 Immediate::getSize(void) const {
      return this->getVectorSize() / BYTE_SIZE_BIT;
    }


    triton::uint32 Immediate::getBitSize(void) const {
      return this->getVectorSize();
    }


    triton::uint32 Immediate::getType(void) const {
      return triton::arch::OP_IMM;
    }


    void Immediate::operator=(const Immediate& other) {
      BitsVector::operator=(other);
      this->copy(other);
    }


    void Immediate::copy(const Immediate& other) {
      this->value = other.value;
    }


    std::ostream& operator<<(std::ostream& stream, const Immediate& imm) {
      stream << "0x" << std::hex << imm.getValue() << ":" << std::dec << imm.getBitSize() << " bv[" << imm.getHigh() << ".." << imm.getLow() << "]";
      return stream;
    }


    std::ostream& operator<<(std::ostream& stream, const Immediate* imm) {
      stream << *imm;
      return stream;
    }


    bool operator==(const Immediate& imm1, const Immediate& imm2) {
      if (imm1.getValue() != imm2.getValue())
        return false;
      if (imm1.getSize() != imm2.getSize())
        return false;
      return true;
    }


    bool operator!=(const Immediate& imm1, const Immediate& imm2) {
      if (imm1 == imm2)
        return false;
      return true;
    }


    bool operator<(const Immediate& imm1, const Immediate& imm2) {
      return imm1.getValue() < imm2.getValue();
    }

  }; /* arch namespace */
}; /* triton namespace */
