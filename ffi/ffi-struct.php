<?php

// Init
$code = "
  typedef struct surfaceData {
    unsigned int atomSerialNumber;
    char chainId[10];
    long double vdw;
  
    long double d[50];
    long double d2[50];
    long double beta[50];
    long double surface;
    long double z;
  
    unsigned int peers[50];
    unsigned int peerCount;
  } surfaceData;


  extern void allocate(unsigned int);
  extern void dispose();
  extern void set(unsigned int index, struct surfaceData* data);
  extern void dump(unsigned int index);
";
$ffi = FFI::cdef($code, "./libshared.so");

// Allocate
//$ffi->allocate(500000);
$ffi->allocate(2000);

// Create entry and add it to the data array
$entry = $ffi->new("struct surfaceData");
$entry->atomSerialNumber = 1678;
$entry->vdw = 1.87 + 1.4;
$entry->z = -7.304;
$entry->peers[0] = 1690;
$entry->peerCount++;
$dy = 1;
$dx = 2;
$entry->d2[0] = $dx*$dx + $dy*$dy;
$entry->d[0] = sqrt($entry->d2[0]);
$entry->beta[0] = atan2($dy, $dx) + M_PI;

$peer = $ffi->new("struct surfaceData");
$peer->atomSerialNumber = 1690;
$peer->vdw = 1.76 + 1.4;
$peer->z = -7.304;


$ptr = FFI::addr($entry);
$ffi->set(1678, $ptr);
$ptr = FFI::addr($peer);
$ffi->set(1690, $ptr);

$ffi->dump(1678);
$ffi->dump(1690);

// Clean up stuff
$ffi->dispose();

