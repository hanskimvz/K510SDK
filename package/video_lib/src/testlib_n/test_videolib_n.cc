/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/******************************************************************************
  File Name     : test_videolib_n.cc
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h> 
#include <assert.h>
#include <errno.h>
#include <pthread.h>

#include <termios.h>
#include <sys/mman.h>
#include <ctype.h>
#include <stdint.h>

#include "isp_com.h"
#include "isp_video.h"

/*******************************memory***************************************/
#define IMAGE_NAME4  "./Canaanlogo_640x480_argb8888_stride2560_rgb.bmp.argb"
#define IMAGE_NAME5  "./Canaanlogo_640x480_argb8888_stride2560_gbr.bmp.argb"
#define IMAGE_NAME6  "./Canaanlogo_640x480_rgb888_stride1920_rgb.bmp.argb"
#define IMAGE_NAME7  "./Canaanlogo_640x480_rgb888_stride1920_bgr.bmp.argb"

#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)


#define MEMORY_TEST_BLOCK_NUM   10          /* 测试多少次申请释放 */
#define MEMORY_TEST_BLOCK_SIZE  4096        /* 测试申请的内存空间大小 */
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* 如果需要mmap映射,对齐需要4K的整数倍 */

#define SHARE_MEMORY_DEV    "/dev/k510-share-memory"
#define MAP_MEMORY_DEV      "/dev/mem"

struct share_memory_alloc_align_args {
    uint32_t size;
    uint32_t alignment;
    uint32_t phyAddr;
};


// share memory 
int *vo_osd_virtual_addr[MEMORY_TEST_BLOCK_NUM] = {0};
int fd_share_memory = -1;
int fd_mem_map = -1;
struct share_memory_alloc_align_args    allocAlignMem[MEMORY_TEST_BLOCK_NUM] = {0};

//
struct video_isp_info
{
    ISP_PIPELINE_E isp_pipeline;
    //
    unsigned int total_width;
    unsigned int total_height;
    //
    unsigned int input_width;
    unsigned int input_height;
    //
    unsigned int output_width;
    unsigned int output_height;
    //
    unsigned int nr3d_en;
    unsigned int nr3d_addr;
    //
    unsigned int ldc_en;
    unsigned int ldc_addr;
    //
    unsigned int main_en;
    unsigned int main_addr;
    //
    unsigned int ds0_en; 
    unsigned int ds0put_width;
    unsigned int ds0put_height;
    unsigned int ds0_addr;  
    //
    unsigned int ds1_en; 
    unsigned int ds1put_width;
    unsigned int ds1put_height;
    unsigned int ds1_addr;
    unsigned int ds1_stride;  
    //
    unsigned int ds2_en; 
    unsigned int ds2put_width;
    unsigned int ds2put_height;
    unsigned int ds2_r_addr;
    unsigned int ds2_g_addr;
    unsigned int ds2_b_addr;
    DS2_RGB_TYPE ds2_rgb_type;
    unsigned int ds2_rgb_stride;
    //
    unsigned int vi_r_tpg_en;
    unsigned int vi_w_tpg_en;
    unsigned int vi_tpg_addr;    
};
//
struct video_vo_info
{
    //layer1
    unsigned int layer1_en;
    unsigned int layer1_width;
    unsigned int layer1_height;
    unsigned int layer1_yAddr0;
    unsigned int layer1_yAddr1; 
    //layer2
    unsigned int layer2_en;
    unsigned int layer2_width;
    unsigned int layer2_height;
    unsigned int layer2_yAddr0;
    unsigned int layer2_yAddr1;
    //osd0 
    unsigned int osd0_en;
    unsigned int osd0_width;
    unsigned int osd0_height;
    unsigned int osd0_rgb_type;    
    unsigned int osd0_yAddr0;
    unsigned int osd0_yAddr1; 
    //osd1
    unsigned int osd1_en; 
    unsigned int osd1_width;
    unsigned int osd1_height;
    unsigned int osd1_rgb_type;    
    unsigned int osd1_yAddr0;
    unsigned int osd1_yAddr1;
    unsigned int osd1_type;
    unsigned int osd1_rgb_rev; 
    //osd2 
    unsigned int osd2_en;
    unsigned int osd2_width;
    unsigned int osd2_height;
    unsigned int osd2_rgb_type;    
    unsigned int osd2_yAddr0;
    unsigned int osd2_yAddr1;
    unsigned int osd2_type;
    unsigned int osd2_rgb_rev;      
};
//
int set_vi_imx385_params(struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    printf("set_vi_params\n");
    struct video_vi_info vi_info;
	vi_info.dphy_mode = 0;//TWO_LANES_MODE;
	vi_info.sony_mode = 0;//SONY_POL_MODE_DIS;

	struct vi_sensor_info *mipi0info = &vi_info.sensor_info[0];
	mipi0info->sensor_interface_en = 1;//ENABLE;
	mipi0info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	mipi0info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	mipi0info->isp_pipeline = isp_info->isp_pipeline;//1;//ISP_F_2K;
	vi_info.sensor_info[1].sensor_interface_en = 0;//DISABLE;
	vi_info.sensor_info[2].sensor_interface_en = 0;//DISABLE;

	struct vi_pipe_info *pipe00_info = &vi_info.pipe_info[0];
	pipe00_info->win_mode_en = 1;//TRUE;	
	pipe00_info->input_ch_sel = 1;//MIPI_INPUT;
	pipe00_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    pipe00_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    pipe00_info->pixel_width = 2;//PIXEL_WIDTH_12BIT;
	pipe00_info->data_out_timming_ctrl = 3;
	pipe00_info->sync_pulse_mode = 0;//0;
	pipe00_info->sen_mipi_clk_pol = 1;
	pipe00_info->sen_mipi_vsync_pol = 0;
	pipe00_info->sen_mipi_hsync_pol = 0;
	pipe00_info->sen_mipi_field_pol = 1;
	pipe00_info->isp_clk_pol = 1;
	pipe00_info->isp_vsync_pol = 1;
	pipe00_info->isp_hsync_pol = 1;
	pipe00_info->isp_field_pol = 1;
	//
    pipe00_info->tpg_w_en = isp_info->vi_w_tpg_en;//0;
    pipe00_info->tpg_r_en = isp_info->vi_r_tpg_en;//0;
    pipe00_info->total_width = isp_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe00_info->total_height = isp_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe00_info->in_width = isp_info->input_width;//isp_size->in_size.Width - 1;//1920;
	pipe00_info->in_height = isp_info->input_height;//isp_size->in_size.Height - 1;//1080;
    pipe00_info->w_st_width = 0x0;
	pipe00_info->w_st_height = 0x3fff;
    pipe00_info->r_st_width = 0x117;
	pipe00_info->r_st_height = 0x2c;
    pipe00_info->vi_pipe_w_addr_y0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_y1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_addr_stride = (pipe00_info->in_width*3/2+15)/16*16;
	pipe00_info->tof_mode_enable = 0;//DISABLE;
	pipe00_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe00_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
    video_set_vi(&vi_info);

    return 0;
}
//
int set_vi_jfx23s_params(struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
	struct video_vi_info vi_info;
	vi_info.dphy_mode = 0;//TWO_LANES_MODE;
	vi_info.sony_mode = 0;//SONY_POL_MODE_DIS;
	struct vi_sensor_info *dvp0info = &vi_info.sensor_info[2]; 
	dvp0info->sensor_interface_en = 1;//ENABLE;
	dvp0info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	dvp0info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	dvp0info->isp_pipeline = isp_info->isp_pipeline;//1;//ISP_F_2K;
	vi_info.sensor_info[0].sensor_interface_en = 0;//DISABLE;
	vi_info.sensor_info[1].sensor_interface_en = 0;//DISABLE;
    //
    struct vi_pipe_info *dvp0_info = &vi_info.pipe_info[6];
	dvp0_info->win_mode_en = 0;//FALSE;		
	dvp0_info->input_ch_sel = 0;//DVP_INPUT;
	dvp0_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    dvp0_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    dvp0_info->pixel_width = 1;//PIXEL_WIDTH_10BIT;
	dvp0_info->data_out_timming_ctrl = 0;//CTRL_CYCLE_DELAY_1;
	dvp0_info->sync_pulse_mode = 1;//0;
	dvp0_info->sen_mipi_clk_pol = 1;//TRUE;
	dvp0_info->sen_mipi_vsync_pol = 1;//TRUE;
	dvp0_info->sen_mipi_hsync_pol = 1;//TRUE;
	dvp0_info->sen_mipi_field_pol = 1;//TRUE;
	dvp0_info->isp_clk_pol = 1;//TRUE;
	dvp0_info->isp_vsync_pol = 1;//TRUE;
	dvp0_info->isp_hsync_pol = 1;//TRUE;
	dvp0_info->isp_field_pol = 1;//TRUE;
    dvp0_info->tpg_w_en = isp_info->vi_w_tpg_en;//DISABLE;
    dvp0_info->tpg_r_en = isp_info->vi_r_tpg_en;//DISABLE;
    dvp0_info->total_width = isp_info->total_width;//2200;
	dvp0_info->total_height = isp_info->total_height;//1125;
    dvp0_info->in_width = isp_info->input_width;//1920;
	dvp0_info->in_height = isp_info->input_height;//1080;
    dvp0_info->w_st_width = 0x24f;//0x0;
	dvp0_info->w_st_height = 0x3fff;
    dvp0_info->r_st_width = 0x0;//0x117;
	dvp0_info->r_st_height = 0x0;//0x2c;
    dvp0_info->vi_pipe_w_addr_y0 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_y1 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_uv0 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_w_addr_uv1 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_r_addr_y0 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_r_addr_y1 = isp_info->vi_tpg_addr;
    dvp0_info->vi_pipe_addr_stride = (isp_info->input_width*10/8+15)/16*16;
	dvp0_info->tof_mode_enable = 0;//DISABLE;
	dvp0_info->vi_pipe_tpg_tof_frm_num = 0x0;
	dvp0_info->vi_pipe_tpg_tof_frm_stride = 0x0;
    video_set_vi(&vi_info);
    return 0;
}
//
int set_vi_imx219_params(struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    printf("set_vi_params\n");
    struct video_vi_info vi_info;
	vi_info.dphy_mode = 0;//TWO_LANES_MODE;
	vi_info.sony_mode = 0;//SONY_POL_MODE_DIS;

	struct vi_sensor_info *mipi0info = &vi_info.sensor_info[0];
	mipi0info->sensor_interface_en = 1;//ENABLE;
	mipi0info->wdr_sensor_vendor = 0;//SONY_WDR_SENSOR;
	mipi0info->wdr_mode = 0;//ISP_PIPE_WDR_NONE;
	mipi0info->isp_pipeline = isp_info->isp_pipeline;//1;//ISP_F_2K;
	vi_info.sensor_info[1].sensor_interface_en = 0;//DISABLE;
	vi_info.sensor_info[2].sensor_interface_en = 0;//DISABLE;

	struct vi_pipe_info *pipe00_info = &vi_info.pipe_info[0];
	pipe00_info->win_mode_en = 1;//TRUE;	
	pipe00_info->input_ch_sel = 1;//MIPI_INPUT;
	pipe00_info->ch_mode_sel = 1;//VI_MIPI_BT1120;
    pipe00_info->pixel_type = 0;//SENSOR_INPUT_RAWRGB;
    pipe00_info->pixel_width = 1;//PIXEL_WIDTH_12BIT;
	pipe00_info->data_out_timming_ctrl = 3;
	pipe00_info->sync_pulse_mode = 0;//0;
	pipe00_info->sen_mipi_clk_pol = 1;
	pipe00_info->sen_mipi_vsync_pol = 0;
	pipe00_info->sen_mipi_hsync_pol = 0;
	pipe00_info->sen_mipi_field_pol = 1;
	pipe00_info->isp_clk_pol = 1;
	pipe00_info->isp_vsync_pol = 1;
	pipe00_info->isp_hsync_pol = 1;
	pipe00_info->isp_field_pol = 1;
	//
    pipe00_info->tpg_w_en = isp_info->vi_w_tpg_en;//0;
    pipe00_info->tpg_r_en = isp_info->vi_r_tpg_en;//0;
    pipe00_info->total_width = isp_info->total_width;//isp_size->total_size.Width - 1;//2200;
	pipe00_info->total_height = isp_info->total_height;//isp_size->total_size.Height - 1;//1125;
    pipe00_info->in_width = isp_info->input_width;//isp_size->in_size.Width - 1;//1920;
	pipe00_info->in_height = isp_info->input_height;//isp_size->in_size.Height - 1;//1080;
    pipe00_info->w_st_width = 0x0;
	pipe00_info->w_st_height = 0x3fff;
    pipe00_info->r_st_width = 0x117;
	pipe00_info->r_st_height = 0x2c;
    pipe00_info->vi_pipe_w_addr_y0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_y1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_w_addr_uv1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y0 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_r_addr_y1 = isp_info->vi_tpg_addr;//isp_addr->vi_tpg_baseaddr;
    pipe00_info->vi_pipe_addr_stride = (pipe00_info->in_width*5/4+15)/16*16;
	pipe00_info->tof_mode_enable = 0;//DISABLE;
	pipe00_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe00_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
    video_set_vi(&vi_info);

    return 0;
}
//
int set_isp_f2k_params(enum _SENSOR_TYPE sensor_type,struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    printf("set_isp_params\n");
    struct isp_common_info commoninfo;
    commoninfo.isp_out_sel = 0;//0:main_out 1;DS0_OUT;
    commoninfo.totalsize_width = isp_info->total_width;//2200;
    commoninfo.totalsize_height = isp_info->total_height;//1125;
    commoninfo.insize_width = isp_info->input_width;//1920;
    commoninfo.insize_height = isp_info->input_height;//1080;
    commoninfo.outsize_width = isp_info->output_width;//1920;
    commoninfo.outsize_height = isp_info->output_height;//1080;
    video_set_ispf2kcommon(sensor_type,&commoninfo);
    //
    struct isp_ds_info ds0_info;
    ds0_info.ds_en = isp_info->ds0_en;//1;
    ds0_info.ds_width = isp_info->ds0put_width;//1080;
    ds0_info.ds_height = isp_info->ds0put_height;//720;
    ds0_info.y_addr0 = isp_info->ds0_addr;//;
    ds0_info.y_addr1 = isp_info->ds0_addr;//; 
    ds0_info.uv_swap = 0;   
    video_set_ispf2kds0(sensor_type,&ds0_info);
    //
    struct isp_ds_info ds1_info;
    ds1_info.ds_en = isp_info->ds1_en;//1;
    ds1_info.ds_width = isp_info->ds1put_width;//1080;
    ds1_info.ds_height = isp_info->ds1put_height;// 720;
    ds1_info.y_addr0 = isp_info->ds1_addr;//;
    ds1_info.y_addr1 = isp_info->ds1_addr;//;
    ds1_info.stride  = isp_info->ds1_stride;
    ds1_info.uv_swap = 0;  
    video_set_ispf2kds1(sensor_type,&ds1_info);
    //
    struct isp_ds2_info ds2_info;
    ds2_info.ds2_en = isp_info->ds2_en;//1;
    ds2_info.ds2_width = isp_info->ds2put_width;//320;
    ds2_info.ds2_height = isp_info->ds2put_height;//256;
    ds2_info.ds2_rgb_type = isp_info->ds2_rgb_type;//DS2_S_RGB;//DS2_ARGB;//;DS2_S_RGB
    ds2_info.stride = isp_info->ds2_rgb_stride;
    ds2_info.r_addr0 = isp_info->ds2_r_addr;//;
    ds2_info.r_addr1 = isp_info->ds2_r_addr;//;
    ds2_info.g_addr0 = isp_info->ds2_g_addr;//;
    ds2_info.g_addr1 = isp_info->ds2_g_addr;//; 
    ds2_info.b_addr0 = isp_info->ds2_b_addr;//;
    ds2_info.b_addr1 = isp_info->ds2_b_addr;//;  
    video_set_ispf2kds2(sensor_type,&ds2_info);

    return 0;
}
//
int set_isp_r2k_params(enum _SENSOR_TYPE sensor_type,struct video_isp_info *isp_info)
{
    ISP_CHECK_POINTER(isp_info);
    struct isp_common_info commoninfo;
    commoninfo.isp_out_sel = 0;//0:main_out 1;DS0_OUT;
    commoninfo.totalsize_width = isp_info->total_width;//2200;
    commoninfo.totalsize_height = isp_info->total_height;//1125;
    commoninfo.insize_width = isp_info->input_width;//1920;
    commoninfo.insize_height = isp_info->input_height;//1080;
    commoninfo.outsize_width = isp_info->output_width;//1920;
    commoninfo.outsize_height = isp_info->output_height;//1080;
    video_set_ispr2kcommon(sensor_type,&commoninfo);
    struct isp_ds_info ds0_info;
    ds0_info.ds_en = isp_info->ds0_en;//1;
    ds0_info.ds_width = isp_info->ds0put_width;//1080;
    ds0_info.ds_height = isp_info->ds0put_height;//720;
    ds0_info.y_addr0 = isp_info->ds0_addr;//;
    ds0_info.y_addr1 = isp_info->ds0_addr;//;
    ds0_info.uv_swap = 0;    
    video_set_ispr2kds0(sensor_type,&ds0_info);
    struct isp_ds_info ds1_info;
    ds1_info.ds_en = isp_info->ds1_en;//1;
    ds1_info.ds_width = isp_info->ds1put_width;//1080;
    ds1_info.ds_height = isp_info->ds1put_height;// 720;
    ds1_info.y_addr0 = isp_info->ds1_addr;//;
    ds1_info.y_addr1 = isp_info->ds1_addr;//;
    ds1_info.stride  = isp_info->ds1_stride; 
    ds1_info.uv_swap = 0; 
    video_set_ispr2kds1(sensor_type,&ds1_info);
    struct isp_ds2_info ds2_info;
    ds2_info.ds2_en = isp_info->ds2_en;//1;
    ds2_info.ds2_width = isp_info->ds2put_width;//320;
    ds2_info.ds2_height = isp_info->ds2put_height;//256;
    ds2_info.ds2_rgb_type = isp_info->ds2_rgb_type;//DS2_S_RGB;//DS2_ARGB;//;DS2_S_RGB
    ds2_info.stride = isp_info->ds2_rgb_stride;
    ds2_info.r_addr0 = isp_info->ds2_r_addr;//;
    ds2_info.r_addr1 = isp_info->ds2_r_addr;//;
    ds2_info.g_addr0 = isp_info->ds2_g_addr;//;
    ds2_info.g_addr1 = isp_info->ds2_g_addr;//; 
    ds2_info.b_addr0 = isp_info->ds2_b_addr;//;
    ds2_info.b_addr1 = isp_info->ds2_b_addr;//;     
    video_set_ispr2kds2(sensor_type,&ds2_info);

    return 0;
}
//
int set_vo_hdmi_params(enum VO_OUT_IMGTYPE imgtype,struct video_vo_info *voInfo)
{
    ISP_CHECK_POINTER(voInfo);
    int v_offset = 0x2a;//14;
    int h_offset = 0xc4;//0xc6;//16;//46;
    int width = 1920;
    int height = 1080;
    struct vo_dispaly_info dispaly_info;
    dispaly_info.dispEnable = 1;
    dispaly_info.vo_out_imgtype = imgtype;//0;
    dispaly_info.xZoneCtl_start = h_offset;//0xC6;
    dispaly_info.xZoneCtl_stop = width + h_offset;//0x846;
    dispaly_info.yZoneCtl_start = v_offset;//0x2A;
    dispaly_info.yZoneCtl_stop = height + v_offset;//0x462;
    dispaly_info.SyncMode = 2;//VO_SYSTEM_MODE_1920x1080x30P;
    dispaly_info.vo_out_active_imgh = width;//1920;
    dispaly_info.vo_out_active_imgv = height;
    video_set_display(&dispaly_info);
    //
    struct vo_layer_info layer1_info;
    layer1_info.layerEn = voInfo->layer1_en;//1;
    layer1_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer1_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer1_info.uvswap = 0;
    //
    layer1_info.offset_hsize = 0;
    layer1_info.offset_vsize = 0;
    layer1_info.in_hsize = voInfo->layer1_width;
    layer1_info.in_vsize = voInfo->layer1_height;
    //		
    layer1_info.layer_x_start = h_offset;
    layer1_info.layer_y_start = v_offset;
    //
    layer1_info.layer_yAddr0 = voInfo->layer1_yAddr0;
    layer1_info.layer_yAddr1 = voInfo->layer1_yAddr1;
    video_set_volayer1(&layer1_info);
    //
    struct vo_layer_info layer2_info;
    layer2_info.layerEn = voInfo->layer2_en;//1;
    layer2_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    layer2_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    layer2_info.uvswap = 0;
    //
    layer2_info.offset_hsize = 0;
    layer2_info.offset_vsize = 0;
    layer2_info.in_hsize = voInfo->layer2_width;
    layer2_info.in_vsize = voInfo->layer2_height;
    //		
    layer2_info.layer_x_start = h_offset + 1200;
    layer2_info.layer_y_start = v_offset;
    //
    layer2_info.layer_yAddr0 = voInfo->layer2_yAddr0;
    layer2_info.layer_yAddr1 = voInfo->layer2_yAddr1;
    video_set_volayer2(&layer2_info);
    //
    struct vo_layer_osd_info osd0_info;
    osd0_info.osdEn = voInfo->osd0_en;//1;
    osd0_info.osdtype = 3;//OSD_RGB_32BIT;
    if( 0 == voInfo->osd0_rgb_type ) //DS2_S_RGB
    {
        osd0_info.osdtype = 1;//OSD_MONOCHROME_8BIT; 
    }
    osd0_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd0_info.rgbrev = 0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd0_info.width = voInfo->osd0_width;
    osd0_info.height = voInfo->osd0_height;
    //
    osd0_info.osd_x_start = h_offset;
    osd0_info.osd_y_start = v_offset + 800;
    //
    osd0_info.alp_addr0 = voInfo->osd0_yAddr0;
    osd0_info.alp_addr1 = voInfo->osd0_yAddr1;
    osd0_info.vlu_addr0 = voInfo->osd0_yAddr0;
    osd0_info.vlu_addr1 = voInfo->osd0_yAddr1;
    video_set_volayer4osd0(&osd0_info);
    //
    struct vo_layer_osd_info osd1_info;
    osd1_info.osdEn = voInfo->osd1_en;//1;
    osd1_info.osdtype = voInfo->osd1_type;//3;//OSD_RGB_32BIT;
    osd1_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd1_info.rgbrev = voInfo->osd1_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd1_info.width = voInfo->osd1_width;
    osd1_info.height = voInfo->osd1_height;
    //
    osd1_info.osd_x_start = h_offset+1280;
    osd1_info.osd_y_start = v_offset+500;
    //
    osd1_info.alp_addr0 = voInfo->osd1_yAddr0;
    osd1_info.alp_addr1 = voInfo->osd1_yAddr1;
    osd1_info.vlu_addr0 = voInfo->osd1_yAddr0;
    osd1_info.vlu_addr1 = voInfo->osd1_yAddr1;
    video_set_volayer5osd1(&osd1_info);
    //
    struct vo_layer_osd_info osd2_info;
    osd2_info.osdEn = voInfo->osd2_en;//1;
    osd2_info.osdtype = voInfo->osd2_type;//3;//OSD_RGB_32BIT;
    osd2_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd2_info.rgbrev = voInfo->osd2_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd2_info.width = voInfo->osd2_width;
    osd2_info.height = voInfo->osd2_height;
    //
    osd2_info.osd_x_start = h_offset+1080;
    osd2_info.osd_y_start = v_offset+600;;
    //
    osd2_info.alp_addr0 = voInfo->osd2_yAddr0;
    osd2_info.alp_addr1 = voInfo->osd2_yAddr1;
    osd2_info.vlu_addr0 = voInfo->osd2_yAddr0;
    osd2_info.vlu_addr1 = voInfo->osd2_yAddr1;
    video_set_volayer6osd2(&osd2_info);
    return 0;
}
//
int set_vo_dsi_params(enum _SENSOR_TYPE sensor_type,enum VO_OUT_IMGTYPE imgtype,struct video_vo_info *voInfo)
{  
    ISP_CHECK_POINTER(voInfo);
    int v_offset = 14;
    int h_offset = 16;//46; 
    struct vo_dispaly_info dispaly_info;
    dispaly_info.dispEnable = 1;
    dispaly_info.vo_out_imgtype = imgtype;//0;

    dispaly_info.xZoneCtl_start = 0x2e;
    dispaly_info.xZoneCtl_stop = 0x465;
    dispaly_info.yZoneCtl_start = 0xe;
    dispaly_info.yZoneCtl_stop = 0x78d;
    dispaly_info.SyncMode = 8;//VO_SYSTEM_MODE_1080x1920x30P;
    dispaly_info.vo_out_active_imgh = 1080;
    dispaly_info.vo_out_active_imgv = 1920;
    video_set_display(&dispaly_info);
    //
    struct vo_layer_info layer1_info;
	layer1_info.layerEn = voInfo->layer1_en;//1;
	layer1_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    if(sensor_type == JFX23S_SENSOR)
    {
        layer1_info.endianuv = 2;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    }
    else
    {
        layer1_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    }    
    layer1_info.uvswap = 0;
    //
    layer1_info.offset_hsize = 0;
    layer1_info.offset_vsize = 0;
    layer1_info.in_hsize = voInfo->layer1_width;
    layer1_info.in_vsize = voInfo->layer1_height;
    //		
    layer1_info.layer_x_start = v_offset;
    layer1_info.layer_y_start = h_offset;
    //
    layer1_info.layer_yAddr0 = voInfo->layer1_yAddr0;
    layer1_info.layer_yAddr1 = voInfo->layer1_yAddr1;
    video_set_volayer1(&layer1_info);
    //
    struct vo_layer_info layer2_info;
	layer2_info.layerEn = voInfo->layer2_en;//1;
	layer2_info.yuvmode = 1;  //1: yuv420/ 0:yuv422
    if(sensor_type == JFX23S_SENSOR)
    {
        layer2_info.endianuv = 2;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    }
    else
    {
        layer2_info.endianuv = 2;//3;//2;//VO_VIDEO_LAYER_UV_ENDIAN_MODE2
    } 
    layer2_info.uvswap = 0;
    //
    layer2_info.offset_hsize = 0;
    layer2_info.offset_vsize = 0;
    layer2_info.in_hsize = voInfo->layer2_width;
    layer2_info.in_vsize = voInfo->layer2_height;
    //		
    layer2_info.layer_x_start = v_offset + 400;
    layer2_info.layer_y_start = h_offset + 730;//1200;
    //
    layer2_info.layer_yAddr0 = voInfo->layer2_yAddr0;
    layer2_info.layer_yAddr1 = voInfo->layer2_yAddr1;
    video_set_volayer2(&layer2_info);
    //
    struct vo_layer_osd_info osd0_info;
    osd0_info.osdEn = voInfo->osd0_en;//1;
    osd0_info.osdtype = 3;//OSD_RGB_32BIT;
    if( 0 == voInfo->osd0_rgb_type ) //DS2_S_RGB
    {
        osd0_info.osdtype = 1;//OSD_MONOCHROME_8BIT; 
    }
    osd0_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd0_info.rgbrev = 0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd0_info.width = voInfo->osd0_width;
    osd0_info.height = voInfo->osd0_height;
    //
    osd0_info.osd_x_start = v_offset;
    osd0_info.osd_y_start = h_offset + 730;
    //
    osd0_info.alp_addr0 = voInfo->osd0_yAddr0;
    osd0_info.alp_addr1 = voInfo->osd0_yAddr1;
    osd0_info.vlu_addr0 = voInfo->osd0_yAddr0;
    osd0_info.vlu_addr1 = voInfo->osd0_yAddr1;
    video_set_volayer4osd0(&osd0_info);
    //
    struct vo_layer_osd_info osd1_info;
    osd1_info.osdEn = voInfo->osd1_en;//1;
    osd1_info.osdtype = voInfo->osd1_type;//3;//OSD_RGB_32BIT;
    osd1_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd1_info.rgbrev = voInfo->osd1_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd1_info.width = voInfo->osd1_width;
    osd1_info.height = voInfo->osd1_height;
    //
    osd1_info.osd_x_start = v_offset;
    osd1_info.osd_y_start = h_offset+1460;
    //
    osd1_info.alp_addr0 = voInfo->osd1_yAddr0;
    osd1_info.alp_addr1 = voInfo->osd1_yAddr1;
    osd1_info.vlu_addr0 = voInfo->osd1_yAddr0;
    osd1_info.vlu_addr1 = voInfo->osd1_yAddr1;
    video_set_volayer5osd1(&osd1_info);
    //
    struct vo_layer_osd_info osd2_info;
    osd2_info.osdEn = voInfo->osd2_en;//1;
    osd2_info.osdtype = voInfo->osd2_type;//3;//OSD_RGB_32BIT;
    osd2_info.alphatpye = 0;//OSD_FIXED_VALUE;
    osd2_info.rgbrev = voInfo->osd2_rgb_rev;//0;//0:OSD_RGB_REV_A,1:OSD_RGB_REV_B
    //
    osd2_info.width = voInfo->osd2_width;
    osd2_info.height = voInfo->osd2_height;
    //
    osd2_info.osd_x_start = v_offset+400;
    osd2_info.osd_y_start = h_offset+1200;
    //
    osd2_info.alp_addr0 = voInfo->osd2_yAddr0;
    osd2_info.alp_addr1 = voInfo->osd2_yAddr1;
    osd2_info.vlu_addr0 = voInfo->osd2_yAddr0;
    osd2_info.vlu_addr1 = voInfo->osd2_yAddr1;
    video_set_volayer6osd2(&osd2_info);       
    //
    return 0;
}


void fun_sig(int sig)
{
    int i = 0;

    if(sig == SIGINT)
    {

        for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {

            if(vo_osd_virtual_addr[i])
                munmap(vo_osd_virtual_addr[i],allocAlignMem[i].size);
        }

        for(i = 0; i < MEMORY_TEST_BLOCK_NUM; i++) {
            if(allocAlignMem[i].phyAddr != 0)
            {
                if(ioctl(fd_share_memory, SHARE_MEMORY_FREE, &allocAlignMem[i].phyAddr) < 0) {
                    printf("share memory  SHARE_MEMORY_FREE error!\r\n");
                }
            }
        }

    }
    exit(0);
}
//
int main(int argc, char **argv)
{
    printf("please input <./test_videolib_n sensor_type lcd_type isp_pipeline debug_en> \n");
    if(argc != 5)
    {        
        printf("sensor_type:IMX219_SENSOR;JFX23S_SENSOR;IMX385_SENSOR;\n");
        printf("lcd_type:HX8399;ITI7807_LCD;AML550_LCD;BT1120_DISPLAY;\n");
        printf("lcd_type:ISP_F_2K;ISP_R_2K;ISP_TOF;\n");
        printf("debug_en:0 -- disable ;1 -- enable;\n");
        return 0;
    }
    printf("sensor_type =%s,lcd_type =%s,isp_pipeline =%s,debug_en =%d\n",argv[1],argv[2],argv[3],atoi(argv[4]));

    FILE *fd4;
    int isp_fd = -1;
    //
    struct video_isp_info isp_info;
    struct video_vo_info voInfo;
    struct isp_int_info  isp_int_info = {0};
    struct vo_disp_irq_info  vo_irq = {0};
    //
    enum _SENSOR_TYPE sensor_type;//JFX23S_SENSOR;//IMX219_SENSOR;//IMX219_SENSOR;//JFX23S_SENSOR;//IMX385_SENSOR;
    if(strcmp(argv[1],"JFX23S_SENSOR") == 0)
    {
        sensor_type = JFX23S_SENSOR;
    }
    else if(strcmp(argv[1],"IMX219_SENSOR") == 0)
    {
        sensor_type = IMX219_SENSOR;
    }
    else if(strcmp(argv[1],"IMX385_SENSOR") == 0)
    {
        sensor_type = IMX385_SENSOR;
    }
    //
    enum _LCD_TYPE lcd_type;//AML550_LCD;//HX8399;//ITI7807_LCD//AML550_LCD;//BT1120_DISPLAY;    
    if(strcmp(argv[2],"AML550_LCD") == 0)
    {
        lcd_type = AML550_LCD;
    }
    else if(strcmp(argv[2],"HX8399") == 0)
    {
        lcd_type = HX8399;
    }  
    else if(strcmp(argv[2],"ITI7807_LCD") == 0)
    {
        lcd_type = ITI7807_LCD;
    } 
    else if(strcmp(argv[2],"BT1120_DISPLAY") == 0)
    {
        lcd_type = BT1120_DISPLAY;
    } 
    //     
    enum VO_OUT_IMGTYPE imgtype = VO_OUT_YUV_HDMI;
    //
    if(strcmp(argv[3],"ISP_F_2K") == 0)
    {
        isp_info.isp_pipeline = ISP_F_2K;
    }
    else if(strcmp(argv[3],"ISP_R_2K") == 0)
    {
        isp_info.isp_pipeline = ISP_R_2K;
    } 
    else if(strcmp(argv[3],"ISP_TOF") == 0)
    {
        isp_info.isp_pipeline = ISP_TOF;
    }       
    unsigned int debug_en = atoi(argv[4]);  

    enum _SENSOR_MODE sensor_mode= IMX219_1920_1080;


    // wait crtl c signl
    signal(SIGINT, fun_sig);

    fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR);
    if(fd_share_memory < 0) {
        printf("open %s error!\r\n",SHARE_MEMORY_DEV);
        return 1 ;
    }

    //
    fd_mem_map = open(MAP_MEMORY_DEV, O_RDWR | O_SYNC);
    if (fd_mem_map < 0) {
        printf("CMEM: failed to open /dev/mem!");
        return 1;
    }

    /* 如果需要mmap映射,需要4K的整数倍 */
    //3dnr
    isp_info.nr3d_en = 0;
    if(1 == isp_info.nr3d_en)
    {
        allocAlignMem[0].size      = MEMORY_TEST_BLOCK_SIZE * 1536 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[0].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[0].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[0]) < 0) {
            printf("d3nr share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("d3nr block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[0].phyAddr,allocAlignMem[0].size,allocAlignMem[0].alignment);
        }

        isp_info.nr3d_addr = allocAlignMem[0].phyAddr;
        printf("d3nr_addr =0x%x\n",isp_info.nr3d_addr);
    }
    //ldc
    isp_info.ldc_en = 0;
    if(1 == isp_info.ldc_en)
    {
        allocAlignMem[1].size      = MEMORY_TEST_BLOCK_SIZE * 2048 ;//MEMORY_TEST_BLOCK_SIZE; 0x400000*2
        allocAlignMem[1].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[1].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[1]) < 0) {
            printf("ldc share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ldc block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[1].phyAddr,allocAlignMem[1].size,allocAlignMem[1].alignment);
        }
        isp_info.ldc_addr = allocAlignMem[1].phyAddr;//isp_size.in_size.Width * isp_size.in_size.Height *20/8;
        printf("ldc_addr =0x%x\n",isp_info.ldc_addr);
    }
    //main
    isp_info.main_en = 0;//0;
    if(1 == isp_info.main_en)
    {
        allocAlignMem[2].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[2].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[2].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[2]) < 0) {
            printf("main share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("main block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[2].phyAddr,allocAlignMem[2].size,allocAlignMem[2].alignment);
        }

        isp_info.main_addr = allocAlignMem[2].phyAddr;//1920*1080*3/2;
        printf("main_out_addr =0x%x\n",isp_info.main_addr);
    }
    //ds0
    isp_info.ds0_en = 1; 
    isp_info.ds0put_width = 1080;
    isp_info.ds0put_height = 720;   
    if(1 == isp_info.ds0_en)
    {
        allocAlignMem[3].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[3].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[3].phyAddr   = 0;

        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[3]) < 0) {
            printf("ds0 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds0 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[3].phyAddr,allocAlignMem[3].size,allocAlignMem[3].alignment);
        }

        allocAlignMem[9].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 10;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[9].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[9].phyAddr   = 0;
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[9]) < 0) {
            printf("twod share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("twod block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[10].phyAddr,allocAlignMem[10].size,allocAlignMem[10].alignment);
        } 
        isp_info.ds0_addr = allocAlignMem[3].phyAddr;//isp_addr.main_out_addr + isp_addr.main_stride * isp_size.out_size.Height *3/2;//1920*1080*3/2;
        printf("ds0_out_addr =0x%x\n",isp_info.ds0_addr);
    }
    //ds1 
    isp_info.ds1_en = 1;//0; 
    isp_info.ds1put_width = 640;//1080;
    isp_info.ds1put_height = 480;//720; 
    isp_info.ds1_stride = (isp_info.ds1put_width+15)/16*16;
    if( 1 == isp_info.ds1_en)
    {
        allocAlignMem[4].size      = MEMORY_TEST_BLOCK_SIZE * 1024 * 10;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[4].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[4].phyAddr   = 0;
    
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[4]) < 0) {
            printf("ds1 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds1 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[4].phyAddr,allocAlignMem[4].size,allocAlignMem[4].alignment);
        }
        
        isp_info.ds1_addr = allocAlignMem[4].phyAddr;//isp_addr.ds0_out_addr + isp_addr.ds0_stride * isp_size.ds0_size.Height *3/2;//1920*1080*3/2;
        printf("ds1_out_addr =0x%x\n",isp_info.ds1_addr);

    } 
    //ds2
    isp_info.ds2_en = 1;
    isp_info.ds2put_width = 320;
    isp_info.ds2put_height = 256; 
    isp_info.ds2_rgb_type = DS2_S_RGB; //DS2_ARGB
    isp_info.ds2_rgb_stride = (isp_info.ds2put_width +15)/16*16;
    if(1 == isp_info.ds2_en)
    {
        allocAlignMem[5].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[5].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[5].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[5]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[5].phyAddr,allocAlignMem[5].size,allocAlignMem[5].alignment);
        }

        isp_info.ds2_r_addr = allocAlignMem[5].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;
        if( DS2_ARGB == isp_info.ds2_rgb_type)
        {
            isp_info.ds2_g_addr = isp_info.ds2_r_addr + isp_info.ds2_rgb_stride*2;
            isp_info.ds2_b_addr = isp_info.ds2_g_addr + isp_info.ds2_rgb_stride*3;
        }
        else if(DS2_S_RGB == isp_info.ds2_rgb_type)
        {
            isp_info.ds2_g_addr = isp_info.ds2_r_addr + isp_info.ds2_rgb_stride *isp_info.ds2put_height;
            isp_info.ds2_b_addr = isp_info.ds2_g_addr + isp_info.ds2_rgb_stride *isp_info.ds2put_height;            
        }
        printf("ds2_out_addr =0x%x\n",isp_info.ds2_r_addr);         
    }
    //vi tpg
    isp_info.vi_r_tpg_en  = 0;//1;//0;
    isp_info.vi_w_tpg_en  = 0;//1;//0;
    if((1 == isp_info.vi_r_tpg_en)||(1 == isp_info.vi_w_tpg_en))
    {
        allocAlignMem[6].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[6].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[6].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[6]) < 0) {
            printf("vi_tpg share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return 1;
        }
        else {
            printf("vi_tpg block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[6].phyAddr,allocAlignMem[6].size,allocAlignMem[6].alignment);
        }
        isp_info.vi_tpg_addr = allocAlignMem[6].phyAddr;   
    }
   //vo osd1
    voInfo.osd1_en = 1;
    if(1 == voInfo.osd1_en)
    {
        allocAlignMem[8].size      = MEMORY_TEST_BLOCK_SIZE * 1024 ;//MEMORY_TEST_BLOCK_SIZE; 1920x1080*3/2+1920*1080
        allocAlignMem[8].alignment = MEMORY_TEST_BLOCK_ALIGN;
        allocAlignMem[8].phyAddr   = 0;
        
        if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem[8]) < 0) {
            printf("ds2 share memory  SHARE_MEMORY_ALIGN_ALLOC error!\r\n");
            return  1;
        }
        else {
            printf("ds2 block alloc:0x%08x,size:%d,align %d\r\n",allocAlignMem[8].phyAddr,allocAlignMem[8].size,allocAlignMem[8].alignment);
        }

        voInfo.osd1_yAddr0 = allocAlignMem[8].phyAddr;// + isp_addr.ds1_stride * isp_size.ds1_size.Height *3/2;

        printf("ds2_out_addr =0x%x\n",voInfo.osd1_yAddr0);

        vo_osd_virtual_addr[0] = (int *)mmap(NULL,allocAlignMem[8].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem_map,allocAlignMem[8].phyAddr);
        if(vo_osd_virtual_addr[0] == MAP_FAILED) {
           printf("share memory  virtual_addr error!\r\n");
           return  1;
        }
    }
    //
    //enum _SENSOR_TYPE sensor_type = JFX23S_SENSOR;//IMX219_SENSOR;//IMX219_SENSOR;//JFX23S_SENSOR;//IMX385_SENSOR;
    //enum _LCD_TYPE lcd_type = AML550_LCD;//HX8399;//ITI7807_LCD//AML550_LCD;//BT1120_DISPLAY;
    //enum VO_OUT_IMGTYPE imgtype = VO_OUT_YUV_HDMI;
    //isp_info.isp_pipeline = ISP_F_2K;
    if(IMX385_SENSOR == sensor_type) 
    {
        isp_info.total_width = 2200;
        isp_info.total_height = 1125;
        isp_info.input_width = 1920;
        isp_info.input_height = 1080;
    }
    else if(JFX23S_SENSOR == sensor_type) 
    {
        isp_info.total_width = 2560;
        isp_info.total_height = 1125;
        isp_info.input_width = 1928;
        isp_info.input_height = 1088;        
    }   
    else if(IMX219_SENSOR == sensor_type) 
    {
        isp_info.total_width = 3476;//3448;
        isp_info.total_height = 1166;
        isp_info.input_width = 1920;
        isp_info.input_height = 1080;        
    }  
    isp_info.output_width = 1920;
    isp_info.output_height = 1080;
    //mipi csi
    if(IMX385_SENSOR == sensor_type)
    {
        unsigned int csi0_pixel_width = PIXEL_WIDTH_12BIT; 
        unsigned int csi1_pixel_width = PIXEL_WIDTH_12BIT;
        video_set_mipicsi(MIPI_2LANE12_RAW12,csi0_pixel_width,csi1_pixel_width);
    }
    else if(IMX219_SENSOR == sensor_type)
    {
        unsigned int csi0_pixel_width = PIXEL_WIDTH_10BIT; 
        unsigned int csi1_pixel_width = PIXEL_WIDTH_10BIT;
        video_set_mipicsi(MIPI_2LANE12_RAW10,csi0_pixel_width,csi1_pixel_width);
    }
    
    if(BT1120_DISPLAY == lcd_type)
    {
        imgtype = VO_OUT_YUV_HDMI;
        //bt1120
        struct hdmi_bt1120_info bt1120_info;
        bt1120_info.bt1120_en = 1;
        bt1120_info.bt_in_sel = SEL_VO;
        bt1120_info.img_hsize_total = 2200;
        bt1120_info.img_vsize_total = 1125;
        bt1120_info.img_hsize = 1920; 
        bt1120_info.img_vsize = 1080;  
        video_set_bt1120(&bt1120_info);
    }
    else
    {
        imgtype = VO_OUT_RGB_DSI;
    }
    //
    if(IMX385_SENSOR == sensor_type)
    {
        set_vi_imx385_params(&isp_info);
    }
    else if(JFX23S_SENSOR == sensor_type)
    {
        set_vi_jfx23s_params(&isp_info);
    }
    else if(IMX219_SENSOR == sensor_type)
    {
        set_vi_imx219_params(&isp_info);
    }
    //
    if(ISP_F_2K == isp_info.isp_pipeline)
    {
        set_isp_f2k_params(sensor_type,&isp_info);
    }
    else if(ISP_R_2K == isp_info.isp_pipeline)
    {
        set_isp_r2k_params(sensor_type,&isp_info);
    }
    //
    voInfo.layer1_en = isp_info.ds0_en;
    voInfo.layer1_width = isp_info.ds0put_width;
    voInfo.layer1_height = isp_info.ds0put_height;
    voInfo.layer1_yAddr0= isp_info.ds0_addr;
    voInfo.layer1_yAddr1= isp_info.ds0_addr;
    // 
    voInfo.layer2_en = isp_info.ds1_en;
    voInfo.layer2_width = isp_info.ds1put_width;
    voInfo.layer2_height = isp_info.ds1put_height;
    voInfo.layer2_yAddr0= isp_info.ds1_addr;
    voInfo.layer2_yAddr1= isp_info.ds1_addr;
    //
    voInfo.osd0_en= isp_info.ds2_en;
    voInfo.osd0_width= isp_info.ds2put_width;
    voInfo.osd0_height= isp_info.ds2put_height;
    voInfo.osd0_rgb_type= isp_info.ds2_rgb_type; 
    voInfo.osd0_yAddr0= isp_info.ds2_r_addr;
    voInfo.osd0_yAddr1= isp_info.ds2_r_addr;
    // 
    voInfo.osd1_en = 1; 
    voInfo.osd1_width = 640;
    voInfo.osd1_height = 480;
    voInfo.osd1_yAddr1 = voInfo.osd1_yAddr0;
    voInfo.osd1_type = 3;
    voInfo.osd1_rgb_rev = 0;
    // 
    voInfo.osd2_en = 1;
    voInfo.osd2_width = 640;
    voInfo.osd2_height = 480;
    voInfo.osd2_yAddr0 = voInfo.osd1_yAddr0;
    voInfo.osd2_yAddr1 = voInfo.osd1_yAddr1;
    voInfo.osd2_type = 3;
    voInfo.osd2_rgb_rev = 0;       
    if(BT1120_DISPLAY == lcd_type)
    {
        set_vo_hdmi_params(imgtype,&voInfo);
    }
    else
    {
        set_vo_dsi_params(sensor_type,imgtype,&voInfo);
    }    
    //
    isp_fd = run_video(sensor_type,sensor_mode, lcd_type,isp_info.isp_pipeline,debug_en);

    if(1 == isp_info.ds1_en)
    {
        int ds1_buf_cout = 10;
        int ds1_size = 640 * 480;
        if (ioctl(isp_fd, ISP_CMD_DS1_ADDR, isp_info.ds1_addr) < 0) 
        {
            printf("Call cmd ISP_CMD_DS1_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_ADDR succss \n");
        if (ioctl(isp_fd, ISP_CMD_DS1_BUFF_COUNT, ds1_buf_cout) < 0)
        {
            printf("Call cmd ISP_CMD_DS1_BUFF_COUNT fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_BUFF_COUNT succss \n");
        if (ioctl(isp_fd, ISP_CMD_SET_DS1_SIZE, ds1_size) < 0)
        {
            printf("Call cmd ISP_CMD_SET_DS1_SIZE fail\n");
        }   
        printf("Call cmd ISP_CMD_SET_DS1_SIZE succss \n");
    }
    if(1 == isp_info.ds0_en)
    {
        if (ioctl(isp_fd, ISP_CMD_DS0_SRC_ADDR, allocAlignMem[3].phyAddr) < 0)
        {
            printf("Call cmd ISP_CMD_DS0_SRC_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS0_SRC_ADDR succss \n");
        if (ioctl(isp_fd, ISP_CMD_DS1_DES_ADDR, allocAlignMem[9].phyAddr) < 0)
        {
            printf("Call cmd ISP_CMD_DS1_DES_ADDR fail\n");
        }   
        printf("Call cmd ISP_CMD_DS1_DES_ADDR succss \n");
    }
    isp_int_info.ds1_en = 0;
    video_set_ispf2kint(&isp_int_info);
    vo_irq.vo_disp_irq0_en = 0;
    video_set_voint(&vo_irq);
    
    //
    int ret =0;
    if( 1 == voInfo.osd1_en)
    {
        if(3 == voInfo.osd1_type) //OSD_RGB_32BIT
        {
            if(1 == voInfo.osd1_rgb_rev) //OSD_RGB_REV_B
            {
                fd4 = fopen(IMAGE_NAME4, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME4, errno);
                    return 1;
                }
                printf("open %s success \n",IMAGE_NAME4);
            }
            else
            {
                fd4 = fopen(IMAGE_NAME5, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME5, errno);
                    return 1;
                }
                printf("open %s success \n",IMAGE_NAME5);
            }  

            ret = fread(vo_osd_virtual_addr[0], voInfo.osd1_width*voInfo.osd1_height*4, 1, fd4);    // 3110400 = 1080 * 1920 * 1.5
            if(ret <= 0)
            {
                printf("read  osd_pic is failed ret is %d \n", ret);
                return 1;
            }

            printf("read  osd_pic is success \n");
        }

        if(0 == voInfo.osd1_type) //OSD_RGB_24BIT
        {
            if(1 == voInfo.osd1_rgb_rev) //OSD_RGB_REV_B
            {
                fd4 = fopen(IMAGE_NAME6, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME6, errno);
                    return 1;
                }
                printf("open %s success \n",IMAGE_NAME6);
            }
            else
            {
                fd4 = fopen(IMAGE_NAME7, "rb");    //IMAGE_NAME   IMAGE_NAME1
                if(fd4 == NULL)
                {
                    printf("open %s failure, errno %d\n", IMAGE_NAME7, errno);
                    return 1;
                }
                printf("open %s success \n",IMAGE_NAME7);
            }  

            ret = fread(vo_osd_virtual_addr[0], voInfo.osd1_width*voInfo.osd1_height*3, 1, fd4);    // 3110400 = 1080 * 1920 * 1.5
            if(ret <= 0)
            {
                printf("read  osd_pic is failed ret is %d \n", ret);
                return 1;
            }
    
            printf("read  osd_pic is success \n");
        }
    }

    ////uart
    //int fd;
    //uart_init(&fd);
//
    //pthread_t uart_pthread;
    //if (pthread_create(&uart_pthread, NULL, tuning_server, &fd) != 0)
    //{
    //    printf("pthread_create failed!\n");
    //    return -1;
    //}
    //unsigned char v_recv[100];
    //int ret1;
    //while(1)
    //{
    //    ret1 = read(fd, &v_recv, 100);
    //    if(ret1)
    //    {
    //        printf("data:%s\n",v_recv);
    //    }        
    //}
    // draw a test box
	frame_coordinate_info test;
	test.startx = 200;
	test.starty = 200;
	test.endx = 400;
	test.endy = 400;
    printf("----------------------------------------------- \n");
    while(1)
    {
        video_draw_frame(1, 0, test);
        printf("open draw_frame \n");
        sleep(20);
        //draw_frame(0, 0, test);
        //printf("close draw_frame \n");
        //sleep(20);
    }
    //
    //debug(1,ISP_PIPE_MODE_F2K);
}