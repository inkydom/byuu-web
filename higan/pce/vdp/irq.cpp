auto VDC::IRQ::poll() -> void {
  uint1 pending = 0;
  pending |= collision.pending & collision.enable;
  pending |= overflow.pending & overflow.enable;
  pending |= coincidence.pending & coincidence.enable;
  pending |= vblank.pending & vblank.enable;
  pending |= transferVRAM.pending & transferVRAM.enable;
  pending |= transferSATB.pending & transferSATB.enable;
  line = pending;
}

auto VDC::IRQ::raise(Line line) -> void {
  if(line == Line::Collision && collision.enable) collision.pending = 1;
  if(line == Line::Overflow && overflow.enable) overflow.pending = 1;
  if(line == Line::Coincidence && coincidence.enable) coincidence.pending = 1;
  if(line == Line::Vblank && vblank.enable) vblank.pending = 1;
  if(line == Line::TransferVRAM && transferVRAM.enable) transferVRAM.pending = 1;
  if(line == Line::TransferSATB && transferSATB.enable) transferSATB.pending = 1;
  poll();
}

auto VDC::IRQ::lower() -> void {
  collision.pending = 0;
  overflow.pending = 0;
  coincidence.pending = 0;
  vblank.pending = 0;
  transferVRAM.pending = 0;
  transferSATB.pending = 0;
  line = 0;
}
