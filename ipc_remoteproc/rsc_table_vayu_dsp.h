/*
 * Copyright (c) 2012-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== rsc_table_vayu_dsp.h ========
 *
 *  Define the resource table entries for all DSP cores. This will be
 *  incorporated into corresponding base images, and used by the remoteproc
 *  on the host-side to allocated/reserve resources.
 *
 */

#ifndef _RSC_TABLE_VAYU_DSP_H_
#define _RSC_TABLE_VAYU_DSP_H_

#include "rsc_types.h"

/* DSP Memory Map */
#define L4_DRA7XX_BASE          0x4A000000

#define L4_PERIPHERAL_L4CFG     (L4_DRA7XX_BASE)
#define DSP_PERIPHERAL_L4CFG    0x4A000000

#define L4_PERIPHERAL_L4PER1    0x48000000
#define DSP_PERIPHERAL_L4PER1   0x48000000

#define L4_PERIPHERAL_L4PER2    0x48400000
#define DSP_PERIPHERAL_L4PER2   0x48400000

#define L4_PERIPHERAL_L4PER3    0x48800000
#define DSP_PERIPHERAL_L4PER3   0x48800000

#define L4_PERIPHERAL_L4EMU     0x54000000
#define DSP_PERIPHERAL_L4EMU    0x54000000

#define L3_PERIPHERAL_DMM       0x4E000000
#define DSP_PERIPHERAL_DMM      0x4E000000

#define PRUSS                   0x4B200000
#define DSP_PRUSS               0x4B200000

#define L3_TILER_MODE_0_1       0x60000000
#define DSP_TILER_MODE_0_1      0x60000000

#define L3_TILER_MODE_2         0x70000000
#define DSP_TILER_MODE_2        0x70000000

#define L3_TILER_MODE_3         0x78000000
#define DSP_TILER_MODE_3        0x78000000

#define DSP_MEM_TEXT            0x95000000
#define DSP_MEM_DATA            0x95400000
#define DSP_MEM_HEAP0           0x95800000
#define DSP_MEM_HEAP1           0x95B00000

#define DSP_MEM_IPC_DATA        0x9F000000
#define DSP_MEM_IPC_VRING       0xA0000000
#define DSP_MEM_RPMSG_VRING0    0xA0000000
#define DSP_MEM_RPMSG_VRING1    0xA0004000
#define DSP_MEM_VRING_BUFS0     0xA0040000
#define DSP_MEM_VRING_BUFS1     0xA0080000


#define PHYS_MEM_SH_DATA	0xa0000000
#define DSP_MEM_SH_DATA		0xe0000000

/*
 * NOTE:
 * To avoid issues with allocation failures with Linux carveout regions, need
 * to use the RSC_CARVEOUT entries with power of 2 page order sizes and aligned
 * on the same page order.
 * The size and the alignment order of entries in the resource table plays a
 * part in avoiding gaps in allocation
 */
#define DSP_MEM_IPC_VRING_SIZE  SZ_1M
#define DSP_MEM_IPC_DATA_SIZE   SZ_1M
#define DSP_MEM_TEXT_SIZE       (SZ_1M * 4)
#define DSP_MEM_DATA_SIZE       (SZ_1M * 4)
#define DSP_MEM_HEAP0_SIZE      (SZ_1M * 2)
#define DSP_MEM_HEAP1_SIZE      (SZ_1M * 1)

/*
 * The following values need to match Linux side device tree reserved
 * memory region start address for specific processor core.
 * The addresses are used to create mmu entry for IPC vrings and buffers
 */
#if defined (VAYU_DSP_1)
#define PHYS_MEM_IPC_VRING      0x99000000
#elif defined (VAYU_DSP_2)
#define PHYS_MEM_IPC_VRING      0x9F000000
#endif

/*
 * Sizes of the virtqueues (expressed in number of buffers supported,
 * and must be power of 2)
 */
#define DSP_RPMSG_VQ0_SIZE      256
#define DSP_RPMSG_VQ1_SIZE      256

/* flip up bits whose indices represent features we support */
#define RPMSG_DSP_C0_FEATURES         1

#define NUM_RSC_ENTRIES 19

struct my_resource_table {
    struct resource_table base;

    UInt32 offset[NUM_RSC_ENTRIES];  /* Should match 'num' in actual definition */

    /* rpmsg vdev entry */
    struct fw_rsc_vdev rpmsg_vdev;
    struct fw_rsc_vdev_vring rpmsg_vring0;
    struct fw_rsc_vdev_vring rpmsg_vring1;

    /* ipcdata carveout entry */
    struct fw_rsc_carveout ipcdata_cout;

    /* text carveout entry */
    struct fw_rsc_carveout text_cout;

    /* data carveout entry */
    struct fw_rsc_carveout data_cout;

    /* heap carveout entry */
    struct fw_rsc_carveout heap0_cout;

    /* heap carveout entry */
    struct fw_rsc_carveout heap1_cout;

    /* trace entry */
    struct fw_rsc_trace trace;

    /* devmem entry */
    struct fw_rsc_devmem devmem0;

    /* devmem entry */
    struct fw_rsc_devmem devmem1;

    /* devmem entry */
    struct fw_rsc_devmem devmem2;

    /* devmem entry */
    struct fw_rsc_devmem devmem3;

    /* devmem entry */
    struct fw_rsc_devmem devmem4;

    /* devmem entry */
    struct fw_rsc_devmem devmem5;

    /* devmem entry */
    struct fw_rsc_devmem devmem6;

    /* devmem entry */
    struct fw_rsc_devmem devmem7;

    /* devmem entry */
    struct fw_rsc_devmem devmem8;

    /* devmem entry */
    struct fw_rsc_devmem devmem9;

    /* devmem entry */
    struct fw_rsc_devmem devmem10;

    /* devmem entry */
    struct fw_rsc_devmem devmem11;
};

#define TRACEBUFADDR (UInt32)&ti_trace_SysMin_Module_State_0_outbuf__A

#pragma DATA_SECTION(ti_ipc_remoteproc_ResourceTable, ".resource_table")
#pragma DATA_ALIGN(ti_ipc_remoteproc_ResourceTable, 4096)

struct my_resource_table ti_ipc_remoteproc_ResourceTable = {
    1,      /* we're the first version that implements this */
    NUM_RSC_ENTRIES,     /* number of entries in the table */
    0, 0,   /* reserved, must be zero */
    /* offsets to entries */
    {
        offsetof(struct my_resource_table, rpmsg_vdev),
        offsetof(struct my_resource_table, ipcdata_cout),
        offsetof(struct my_resource_table, text_cout),
        offsetof(struct my_resource_table, data_cout),
        offsetof(struct my_resource_table, heap0_cout),
        offsetof(struct my_resource_table, heap1_cout),
        offsetof(struct my_resource_table, trace),
        offsetof(struct my_resource_table, devmem0),
        offsetof(struct my_resource_table, devmem1),
        offsetof(struct my_resource_table, devmem2),
        offsetof(struct my_resource_table, devmem3),
        offsetof(struct my_resource_table, devmem4),
        offsetof(struct my_resource_table, devmem5),
        offsetof(struct my_resource_table, devmem6),
        offsetof(struct my_resource_table, devmem7),
        offsetof(struct my_resource_table, devmem8),
        offsetof(struct my_resource_table, devmem9),
        offsetof(struct my_resource_table, devmem10),
        offsetof(struct my_resource_table, devmem11),
    },

    /* rpmsg vdev entry */
    {
        TYPE_VDEV, VIRTIO_ID_RPMSG, 0,
        RPMSG_DSP_C0_FEATURES, 0, 0, 0, 2, { 0, 0 },
        /* no config data */
    },
    /* the two vrings */
    { DSP_MEM_RPMSG_VRING0, 4096, DSP_RPMSG_VQ0_SIZE, 1, 0 },
    { DSP_MEM_RPMSG_VRING1, 4096, DSP_RPMSG_VQ1_SIZE, 2, 0 },

    {
        TYPE_CARVEOUT,
        DSP_MEM_IPC_DATA, 0,
        DSP_MEM_IPC_DATA_SIZE, 0, 0, "DSP_MEM_IPC_DATA",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_TEXT, 0,
        DSP_MEM_TEXT_SIZE, 0, 0, "DSP_MEM_TEXT",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_DATA, 0,
        DSP_MEM_DATA_SIZE, 0, 0, "DSP_MEM_DATA",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_HEAP0, 0,
        DSP_MEM_HEAP0_SIZE, 0, 0, "DSP_MEM_HEAP0",
    },

    {
        TYPE_CARVEOUT,
        DSP_MEM_HEAP1, 0,
        DSP_MEM_HEAP1_SIZE, 0, 0, "DSP_MEM_HEAP1",
    },

    {
        TYPE_TRACE, TRACEBUFADDR, 0x8000, 0, "trace:dsp",
    },

    {
        TYPE_DEVMEM,
        DSP_MEM_IPC_VRING, PHYS_MEM_IPC_VRING,
        DSP_MEM_IPC_VRING_SIZE, 0, 0, "DSP_MEM_IPC_VRING",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_0_1, L3_TILER_MODE_0_1,
        SZ_256M, 0, 0, "DSP_TILER_MODE_0_1",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_2, L3_TILER_MODE_2,
        SZ_128M, 0, 0, "DSP_TILER_MODE_2",
    },

    {
        TYPE_DEVMEM,
        DSP_TILER_MODE_3, L3_TILER_MODE_3,
        SZ_128M, 0, 0, "DSP_TILER_MODE_3",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4CFG, L4_PERIPHERAL_L4CFG,
        SZ_16M, 0, 0, "DSP_PERIPHERAL_L4CFG",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4PER1, L4_PERIPHERAL_L4PER1,
        SZ_2M, 0, 0, "DSP_PERIPHERAL_L4PER1",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4PER2, L4_PERIPHERAL_L4PER2,
        SZ_4M, 0, 0, "DSP_PERIPHERAL_L4PER2",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4PER3, L4_PERIPHERAL_L4PER3,
        SZ_8M, 0, 0, "DSP_PERIPHERAL_L4PER3",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_L4EMU, L4_PERIPHERAL_L4EMU,
        SZ_16M, 0, 0, "DSP_PERIPHERAL_L4EMU",
    },

    {
        TYPE_DEVMEM,
        DSP_PERIPHERAL_DMM, L3_PERIPHERAL_DMM,
        SZ_1M, 0, 0, "DSP_PERIPHERAL_DMM",
    },

    {
        TYPE_DEVMEM,
        DSP_PRUSS, PRUSS,
        SZ_1M, 0, 0, "PRUSS_PERIPHERAL",
    },

    {
        TYPE_DEVMEM,
	DSP_MEM_SH_DATA, PHYS_MEM_SH_DATA,
        SZ_256M, 0, 0, "DSP_SH_MEM",
    },

};

#endif /* _RSC_TABLE_VAYU_DSP_H_ */
