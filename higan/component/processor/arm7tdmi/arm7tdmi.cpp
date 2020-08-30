#include <emulator/emulator.hpp>
#include "arm7tdmi.hpp"

namespace higan {

#include "registers.cpp"
#include "memory.cpp"
#include "algorithms.cpp"
#include "instruction.cpp"
#include "instructions-arm.cpp"
#include "instructions-thumb.cpp"
#include "serialization.cpp"

#if !defined(NO_EVENTINSTRUCTION_NOTIFY)
#include "disassembler.cpp"
#endif

ARM7TDMI::ARM7TDMI() {
  armInitialize();
  thumbInitialize();
}

auto ARM7TDMI::power() -> void {
  processor = {};
  processor.r15.modify = [&] { pipeline.reload = true; };
  pipeline = {};
  carry = 0;
  irq = 0;
  cpsr().f = 1;
  exception(PSR::SVC, 0x00);
}

}
