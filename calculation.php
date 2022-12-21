<?php

const ZMAX = 20;
const PROBE_SIZE = 1.4;
const ATOM_COUNT = 90000;
const NEIGHBOUR_COUNT = 30;

$peerZ = 0.1;
$z = 0.02;
$peerVdw = 5;

class B {
  public float $vdw = 1.89;
  public function __construct() { }

  public function vdwWithProbeSize(): float {
    return $this->vdw + PROBE_SIZE;
  }
}
$b = new B();

// $start = microtime(true);
// for ($atoms = 0; $atoms < ATOM_COUNT; $atoms++) {
//   for ($peer = 0; $peer < NEIGHBOUR_COUNT; $peer++) {
//     for ($z = 0; $z < ZMAX; $z++) {
//       $peerVdw = $b->vdwWithProbeSize();
//       if (abs($peerZ - $z) >= $peerVdw) {
//           continue;
//       }
//     }
//   }
// }
// echo "With abs() time = " . (microtime(true) - $start) . "\n";

$start = microtime(true);
for ($atoms = 0; $atoms < ATOM_COUNT; $atoms++) {
  for ($peer = 0; $peer < NEIGHBOUR_COUNT; $peer++) {
    for ($z = 0; $z < ZMAX; $z++) {
      $peerVdw = $b->vdwWithProbeSize();
      $diff = $peerZ - $z;
      if (($diff < 0 ? -$diff : $diff) >= $peerVdw) {
          continue;
      }
    }
  }
}
echo "Without abs() time = " . (microtime(true) - $start) . "\n";

// $rb2 = $peerVdw * $peerVdw - ($peerZ - $z) * ($peerZ - $z);
// $rb = sqrt($rb2);
// $rarbDifference = abs($ra - $rb);

