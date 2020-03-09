auto CPU::IRQ::pending() const -> bool {
  return pendingIRQ;
}

auto CPU::IRQ::vector() const -> uint16 {
  return pendingVector;
}

auto CPU::IRQ::poll() -> void {
  pendingIRQ = false;
  if(cpu.r.p.i) return;

  if(0) {  //external IRQ sources
    pendingIRQ = !disableExternal;
    pendingVector = 0xfff6;
  }

  if(!disableVDC && (vdp.vdc0.irqLine() | vdp.vdc1.irqLine())) {
    pendingIRQ = !disableVDC;
    pendingVector = 0xfff8;
  }

  if(cpu.timer.irqLine() && cpu.timer.enable) {
    pendingIRQ = !disableTimer;
    pendingVector = 0xfffa;
  }
}
