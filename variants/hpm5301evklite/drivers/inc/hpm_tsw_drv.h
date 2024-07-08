/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TSW_DRV_H
#define HPM_TSW_DRV_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_tsw_regs.h"

#define MAC_LO(mac) (uint32_t)(mac[0] | (mac[1] << 8) | (mac[2] << 16) | (mac[3] << 24))
#define MAC_HI(mac) (uint32_t)(mac[4] | (mac[5] << 8))

#define MAC_MDIO_CTRL_OP_WR (0x01)
#define MAC_MDIO_CTRL_OP_RD (0x02)

typedef struct {
    union {
        uint32_t tx_hdr0;
        struct {
            uint32_t dest_port: 8; /**< dest port */
            uint32_t          : 8; /**< reserved */
            uint32_t queue    : 3; /**< the priority queue for TSW TX */
            uint32_t utag     : 3; /**< TSW-EP TX user sideband information */
            uint32_t          : 6; /**< reserved */
            uint32_t htype    : 4; /**< header type */
        } tx_hdr0_bm;
    };

    union {
        uint32_t tx_hdr1;
        struct {
            uint32_t cb: 32; /**< CB field. Optionally used for external stream identification */
        } tx_hdr1_bm;
    };

    uint32_t tx_hdr2; /**< reserved */
    uint32_t tx_hdr3; /**< reserved */
} tx_hdr_desc_t;

typedef enum {
  tsw_port_speed_10mbps   = 2,
  tsw_port_speed_100mbps  = 3,
  tsw_port_speed_1000mbps = 0
} tsw_port_speed_t;

typedef enum {
  tsw_port_phy_itf_mii   = 0,
  tsw_port_phy_itf_rmii  = 4,
  tsw_port_phy_itf_rgmii = 1
} tsw_port_phy_itf_t;

typedef enum {
  tsw_dst_port_null = 0,
  tsw_dst_port_cpu  = 1 << 0,
  tsw_dst_port_1    = 1 << 1,
  tsw_dst_port_2    = 1 << 2,
  tsw_dst_port_3    = 1 << 3,
} tsw_dst_t;

typedef enum {
  tsw_mac_mode_mii = 0,
  tsw_mac_mode_gmii
} tsw_mac_mode_t;

#if defined __cplusplus
extern "C" {
#endif /* __cplusplus */

hpm_stat_t tsw_send(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id);
hpm_stat_t tsw_recv_setup(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id);
uint32_t tsw_recv(TSW_Type *ptr, uint32_t *buffer, uint32_t length, uint8_t id);

void tsw_mac_lookup_bypass(TSW_Type *ptr, uint8_t dst_port);
void tsw_set_cam_vlan_port(TSW_Type *ptr);

hpm_stat_t tsw_ep_set_mdio_config(TSW_Type *ptr, uint8_t port, uint8_t clk_div);
hpm_stat_t tsw_ep_mdio_read(TSW_Type *ptr, uint8_t port, uint32_t phy_addr, uint32_t reg_addr, uint16_t *data);
hpm_stat_t tsw_ep_mdio_write(TSW_Type *ptr, uint8_t port, uint32_t phy_addr, uint32_t reg_addr, uint16_t data);

hpm_stat_t tsw_ep_enable_mac_ctrl(TSW_Type *ptr, uint8_t port, uint8_t mac_type, bool enable);
hpm_stat_t tsw_ep_set_mac_addr(TSW_Type *ptr, uint8_t port, uint8_t *mac_addr, bool promisc);
hpm_stat_t tsw_ep_set_mac_mode(TSW_Type *ptr, uint8_t port, uint8_t gmii);

void tsw_port_gpr(TSW_Type *ptr, uint8_t port, uint8_t speed, uint8_t itf, uint8_t tx_dly, uint8_t rx_dly);
void tsw_set_internal_frame_action(TSW_Type *ptr, uint8_t dest_port);
void tsw_set_broadcast_frame_action(TSW_Type *ptr, uint8_t dest_port);
void tsw_set_unknown_frame_action(TSW_Type *ptr, uint8_t dest_port);
void tsw_set_lookup_table(TSW_Type *ptr, uint16_t entry_num, uint8_t dest_port, uint64_t dest_mac);

void tsw_clear_cam(TSW_Type *ptr);

#if defined __cplusplus
}
#endif /* __cplusplus */

#endif /* HPM_TSW_DRV_H */