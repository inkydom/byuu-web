auto System::serialize() -> serializer {
  serializer s(information.serializeSize);

  uint signature = 0x31545342;
  char version[16] = {};
  char description[512] = {};
  memory::copy(&version, (const char*)SerializerVersion, SerializerVersion.size());

  s.integer(signature);
  s.array(version);
  s.array(description);
  serializeAll(s);
  s.integer(information.serializeSize);
  return s;
}

auto System::unserialize(serializer& s) -> bool {
  array_view<uint8_t> view{s.data() + s.capacity() - 4, 4};
  auto size = view.readl(4);
  if(size != information.serializeSize) return false;

  uint signature = 0;
  char version[16] = {};
  char description[512] = {};

  s.integer(signature);
  s.array(version);
  s.array(description);

  if(signature != 0x31545342) return false;
  if(string{version} != SerializerVersion) return false;

  power();
  serializeAll(s);
  return true;
}

//internal

auto System::serialize(serializer& s) -> void {
}

auto System::serializeAll(serializer& s) -> void {
  system.serialize(s);
  cartridge.serialize(s);
  cpu.serialize(s);
  apu.serialize(s);
  vpu.serialize(s);
  psg.serialize(s);
}

auto System::serializeInit() -> void {
  serializer s;

  uint signature = 0;
  char version[16] = {};
  char description[512] = {};

  s.integer(signature);
  s.array(version);
  s.array(description);
  serializeAll(s);
  information.serializeSize = s.size() + 4;
  s.integer(information.serializeSize);
}
