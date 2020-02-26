//Hudson Soft HuC6280

struct CPU : HuC6280, Thread {
  Node::Component node;
  Node::Instruction eventInstruction;
  Node::Notification eventInterrupt;
  Memory::Writable<uint8> ram;   //PC Engine = 8KB, SuperGrafx = 32KB
  Memory::Writable<uint8> bram;  //PC Engine CD-ROM Backup RAM = 2KB

  //cpu.cpp
  auto load(Node::Object, Node::Object) -> void;
  auto unload() -> void;

  auto main() -> void;
  auto step(uint clocks) -> void override;
  auto power() -> void;
  auto lastCycle() -> void override;

  //io.cpp
  auto read(uint8 bank, uint13 address) -> uint8 override;
  auto write(uint8 bank, uint13 address, uint8 data) -> void override;
  auto store(uint2 address, uint8 data) -> void override;

  //timer.cpp
  auto timerStep(uint clocks) -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

private:
  struct IRQ {
    //irq.cpp
    auto pending() const -> bool;
    auto vector() const -> uint16;
    auto poll() -> void;

  private:
    bool   disableExternal = 0;
    bool   disableVDC = 0;
    bool   disableTimer = 0;

    bool   pendingIRQ = 0;
    uint16 pendingVector;

    friend class CPU;
  } irq;

  struct Timer {
    inline auto irqLine() const { return line; }

    //timer.cpp
    auto start() -> void;
    auto step(uint clocks) -> void;

  private:
    bool  enable = 0;
    uint7 latch;
    uint7 value;
    uint  clock = 0;

    bool  line = 0;

    friend class CPU;
  } timer;

  struct IO {
    uint8 mdr;
  } io;
};

extern CPU cpu;
