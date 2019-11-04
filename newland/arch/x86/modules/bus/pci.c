/**
  * NewLand Kernel - (C) 2019 Tristan Ross
  */
#include <newland/arch/io.h>
#include <newland/bus.h>
#include <newland/log.h>
#include <newland/module.h>
#include <newland/types.h>

#define PCI_ADDR_PORT 0xCF8
#define PCI_VAL_PORT 0xCFC

#define PCI_VENDOR_ID 0x00
#define PCI_DEVICE_ID 0x02
#define PCI_COMMAND 0x04
#define PCI_STATUS 0x06
#define PCI_REVISION_ID 0x08

#define PCI_PROG_IF 0x09
#define PCI_SUBCLASS 0x0a
#define PCI_CLASS 0x0b
#define PCI_CACHE_LINE_SIZE 0x0c
#define PCI_LATENCY_TIMER 0x0d
#define PCI_HEADER_TYPE 0x0e
#define PCI_BIST 0x0f
#define PCI_BAR0 0x10
#define PCI_BAR1 0x14
#define PCI_BAR2 0x18
#define PCI_BAR3 0x1C
#define PCI_BAR4 0x20
#define PCI_BAR5 0x24

#define PCI_INTERRUPT_LINE 0x3C

#define PCI_SECONDARY_BUS 0x19

#define PCI_HEADER_TYPE_DEVICE 0
#define PCI_HEADER_TYPE_BRIDGE 1
#define PCI_HEADER_TYPE_CARDBUS 2

#define PCI_TYPE_BRIDGE 0x0604

#define pci_extract_bus(dev) ((dev) >> 16)
#define pci_extract_slot(dev) ((dev) >> 8)
#define pci_extract_func(dev) ((dev))
#define pci_getaddr(dev, field) 0x80000000 | (pci_extract_bus((dev)) << 16) | (pci_extract_slot((dev)) << 11) | (pci_extract_func((dev)) << 8) | ((field) & 0xFC)
#define pci_findtype(dev) (read_field(dev, PCI_CLASS, 1) << 8) | read_field(dev, PCI_SUBCLASS, 1)
#define pci_boxdev(bus, slot, func) (((bus) << 16) | ((slot) << 8) | (func))

/** Read & Write **/
static void write_field(uint32_t dev, int field, uint32_t value) {
  outl(PCI_ADDR_PORT, pci_getaddr(dev, field));
  outl(PCI_VAL_PORT, value);
}

static uint32_t read_field(uint32_t dev, int field, int size) {
  outl(PCI_ADDR_PORT, pci_getaddr(dev, field));
  switch (size) {
    case 1: return inb(PCI_VAL_PORT + (field & 3));
    case 2: return inw(PCI_VAL_PORT + (field & 2));
    case 4: return inl(PCI_VAL_PORT);
    default: return 0xFFFF;
  }
}

/** Module Stuff **/
MODULE_INIT(bus_pci) {
  int r = register_bus(NULL, "pci");
  if (r < 0) return r;
  return 0;
}

MODULE_FINI(bus_pci) {
  unregister_bus("pci");
}

MODULE(bus_pci, "Tristan Ross", "GPL", "0.1.0");
