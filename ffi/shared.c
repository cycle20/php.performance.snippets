#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define PDB_ZSLICE 0.05
#define MAX_PEER_COUNT 50
#define MAX_CHAIN_ID_LENGTH 10

extern unsigned short getMaxPeerCount() {
  return MAX_PEER_COUNT;
}

extern unsigned short getMaxChainIdLength() {
  return MAX_CHAIN_ID_LENGTH;
}


extern int array[];

int array[10] = {
  1, 1, 1, 1, 1,
  2, 1, 2, 1, 7,
};

extern void update() {
  array[3] = 13;
}


//
// For complex comparision
//

struct surfaceData {
//typedef struct {
  unsigned int atomSerialNumber;
  char chainId[MAX_CHAIN_ID_LENGTH];
  long double vdw;

  long double d[MAX_PEER_COUNT];
  long double d2[MAX_PEER_COUNT];
  long double beta[MAX_PEER_COUNT];
  long double surface;
  long double z;

  unsigned int peers[MAX_PEER_COUNT];
  unsigned int peerCount;
//} surfaceData;
};
typedef struct surfaceData surfaceData;

surfaceData* surfaceDataArray;

// memory "management"
extern void allocate(unsigned int count) {
  printf("Allocating %d items...\n", count);
  size_t itemSize = sizeof(surfaceData);
  surfaceDataArray = (surfaceData*)calloc(count, itemSize);
  if (surfaceDataArray == NULL) {
    perror("allocate() error");
    return;
  }
  printf("%.2f MB allocated\n", count * (int)itemSize / 1024.0 / 1024);
}

extern void dispose() {
  free(surfaceDataArray);
}

// data access
extern void set(unsigned int index, surfaceData* data) {
  surfaceDataArray[index] = *data;
}

extern void dump(unsigned int index) {
  surfaceData* element = &surfaceDataArray[index];
  printf(
    "ASN: %d, VDW: %.3Lf, z: %.3Lf, surface: %.3Lf, # of peers: %d, beta[0]: %.3Lf\n",
    element->atomSerialNumber,
    element->vdw,
    element->z,
    element->surface,
    element->peerCount,
    element->beta[0]
  );
}

