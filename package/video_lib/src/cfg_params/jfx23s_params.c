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
  File Name     : jfx23s_params.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#include "isp_com.h"
#include "isp_2k/isp_f2k.h"
#include "isp_2k/isp_r2k.h"
#include "vi/vi_com.h"
#include "mipi/mipi.h"
#include "vo/vo.h"

#define WIDTH (1920)
#define HEIGHT (1080)

//
ISP_WRAP_CFG_INFO jfx23s_wrap_info =
{
	MAIN_OUT,//isp_out_sel;
	BT1120_MIPI,//dvp_ch_mode;
    0,//hist_3a_out_en;
	{
        0,//wdr_mode ;
        0,//wdr_long_ch_mode; 	
        0,//wdr_long_l2_buf_en;
        0,//wdr_short_s1_buf_en; 
        0,//wdr_dynamic_switch_en;
        0,//wdr_long_l2_buf_depth;	
        ISP_RGBRAW_DATA,//wdr_long_img_format;   
        IN_YUV422,//wdr_long_yuv_in_format;   
        IN_YUV422,//wdr_long_img_out_format;  
        YUYV,//wdr_long_yuv422_pxl_order;
        PIXEL_12,//wdr_long_pixel_width;
        0x0,//wdr_buf_base;        
        0x0,//wdr_line_stride;	
        0x0,//wdr_frame_buf_size;		        
    },//ISP_WRAP_WDR_S    wdrInfo;
	{
        0,//nr3d_en ;
        0,//nr3d_fbcd_en;
        0,//nr3d_mv_out_en;
        ISP_RGBRAW_DATA,//nr3d_y_img_format; 
        IN_YUV422,//nr3d_y_yuv_in_format;   
        IN_YUV422,//nr3d_y_img_out_format;  
        YUYV,//nr3d_y_yuv422_pxl_order;
        PIXEL_12,//nr3d_y_pixel_width; 
        ISP_RGBRAW_DATA,//nr3d_uv_img_format; 
        IN_YUV422,//nr3d_uv_yuv_in_format;  
        IN_YUV422,//nr3d_uv_mig_out_format; 
        YUYV,//nr3d_uv_yuv422_pxl_order
        PIXEL_8,//nr3d_uv_pixel_width;    
        0x06000000,//nr3d_y_buf_base; 
        0x06300000,//nr3d_uv_buf_base;       
        0xb40,//nr3d_y_line_stride;
        0x780,//nr3d_uv_line_stride;
        0,//nr3d_frame_buf_size;	        
    },//ISP_WRAP_3DNR_S   nr3dInfo;
	{
        0,//ldc_en;
        0x06500000,//ldc_y_buf_base; 
        0x06900000,//ldc_uv_buf_base; 
        0x800,//ldc_line_stride; 
        0x800,//ldc_frame_buf_size;        
    },//ISP_WRAP_LDC_S    ldcInfo;
	{
        0,//main_out_en;
        {
            WIDTH,
            HEIGHT,
        },//main_size;
        0,//main_pix_remap_en;
        ISP_YUV_DATA,//main_out_img_format;   
        IN_YUV422,//main_out_yuv_in_format;  
        IN_YUV420,//main_out_img_out_format; 
        YUYV,//main_out_yuv422_pxl_order
        PIXEL_8,//main_out_pxl_width;	
        0x05000000,//main_y_buf0_base;   
        0x05000000,//main_y_buf1_base;
        0x051fa400,//main_uv_buf0_base;   
        0x051fa400,//main_uv_buf1_base;       
        0x780,//main_line_stride; 
        2048,//main_frame_buf_size;	        
    },//ISP_WRAP_MAIN_S	  mainInfo;
	{
        0,//ds0_out_en;
        0,//ds0_osd0_en ;   
        0,//ds0_osd1_en ; 
        0,//ds0_osd2_en ;
        0,//pix_remap_out0_en;		 	
        {
            WIDTH,
            HEIGHT,
        },//ds0_size;
        ISP_YUV_DATA,//ds0_out_img_format;   
        IN_YUV422,//ds0_out_yuv_in_format;   
        IN_YUV420,//ds0_out_img_out_format;  
        YUYV,//ds0_out_yuv422_pxl_order;
        PIXEL_8,//ds0_out_pxl_width;	
        0x05400000,//ds0_y_buf0_base;   
        0x05400000,//ds0_y_buf1_base;
        0x055fa400,//ds0_uv_buf0_base;   
        0x055fa400,//ds0_uv_buf1_base;       
        0x780,//ds0_line_stride;
        2048,//ds0_frame_buf_size;	         
    },//ISP_WRAP_DS0_S	  ds0Info;
	{
        0,//ds1_out_en;
        0,//ds1_osd0_en ;   
        0,//ds1_osd1_en ; 
        0,//ds1_osd2_en ;
        0,//pix_remap_out1_en;		 	
        {
            WIDTH,
            HEIGHT,
        },//ds1_size;
        ISP_YUV_DATA,//ds1_out_img_format;   
        IN_YUV422,//ds1_out_yuv_in_format;   
        IN_YUV420,//ds1_out_img_out_format;  
        YUYV,//ds1_out_yuv422_pxl_order;
        PIXEL_8,//ds1_out_pxl_width;	
        0x05600000,//ds1_y_buf0_base;   
        0x05600000,//ds1_y_buf1_base;
        0x057fa400,//ds1_uv_buf0_base;   
        0x057fa400,//ds1_uv_buf1_base;  
        0x780,//ds1_line_stride;
        2048,//ds1_frame_buf_size;	         
    },//ISP_WRAP_DS1_S	  ds1Info;
	{
        0,//ds2_out_en;
        0,//ds2_osd0_en ;   
        0,//ds2_osd1_en ; 
        0,//ds2_osd2_en ; 	 		
        {
            WIDTH,
            HEIGHT,            
        },//ds2_size;
        ISP_RGBRAW_DATA,//ds2_out_img_format;   
        IN_YUV422,//ds2_out_yuv_in_format;  
        OUT_ARGB,//ds2_out_img_out_format; 
        YUYV,//ds2_out_yuv422_pxl_order
        PIXEL_8,//ds2_out_pxl_width;	
        0x05700000,//ds2_r_buf0_base;   
        0x05700000,//ds2_r_buf1_base;
        0x05700000,//ds2_g_buf0_base;   
        0x05700000,//ds2_g_buf1_base; 
        0x05700000,//ds2_b_buf0_base;   
        0x05700000,//ds2_b_buf1_base;      
        0x780,//ds2_line_stride; 
        2048,//ds2_frame_buf_size;	        
    },//ISP_WRAP_DS2_S	  ds2Info;
};
//
ISP_CORE_CFG_INFO jfx23s_core_info =
{
//itc
	{
 	    ISP_SYNC_POL_LOW, //hsync_pol
	    ISP_SYNC_POL_LOW, //vsync_pol
	    HSYNC_BASE_ON_INPUT_GEN_BY_ISP, //hsync_input_timing
	    VSYNC_BASE_ON_INPUT, //  vsync_input_timing
	    0,                  //flip_ctl
        ISP_RGBRAW_DATA,    //video_fmt_sel
        {
            2200, //total Width
            1125, //total Height
        },
        {
	        0x05,//05,//Width_st
	        0x17,//18,//Height_st	
	        WIDTH,//Width
	        HEIGHT,//Height	
        },
    },
//tpg   
	{
        0,//tpg_en
        0x9,//tpg_sel
        0x3,//bayer_mode_sel BGGR/RGGB /GRGB/GBGR
        0x0,//motion_mode_sel
        0x0,//wdr_l_mul_data
        0x0,//wdr_m_mul_data
        0x0,//wdr_s_mul_data
    },
//blc   
	{
        1,//blc_en    
        0x0,//blc_offset
        0x100,//blc_ratio
    },
//lsc   
	{
        0,//lsc_en;      
        WIDTH/2,//lsc_h_center;1920/2
        HEIGHT/2,//lsc_v_center;1080/2
        0x100,//lsc_r_ratio; 
        0x100,//lsc_g_ratio; 
        0x100,//lsc_b_ratio; 
        0x100,//lsc_ir_ratio;
    },
//ae
	{
        1,//ae_as_en; 
        1,//ae_ag_en;      
        0,//ae_airis_en;      
        AE_LOCK_64FRAME,//ae_enter_ls_sel; 
        AE_LOCK_32FRAME,//ae_exit_ls_sel;     
        AE_WHOLE_PIC,//ae_win_mode_sel;    
        AE_NORMAL_MODE,//ae_back_light_mode_sel;
        0,//ae_day_change_en;    
        AE_DAY,//ae_day_change_sel;
        {
            0,//Width_st;
            0,//Height_st;
            WIDTH-1,//Width;
            HEIGHT-1,//Height;	            
        },//ae_win_size;
        0x50,//ae_tar_bright;    
        0x8,//ae_tar_bright_range;     
        0x400,//ae_l_ex_time;
        0x10,//ae_m_ex_time;
        0x1,//ae_s_ex_time;     
        0x0,//ae_agc;       
        0x1,//ae_ad_shuttle_freq;
        0x1,//ae_ad_gain_freq;    
        0x20,//ae_adjust_step_max;     
        0x3ff,//ae_ex_value_max;  
        0x1ff,//ae_ex_value_mid;    
        0x100,//ae_ex_value_min;     
        0x900,//ae_gain_value_max;    
        0x200,//ae_gain_value_mid;
        0x4,//ae_gain_value_min;    
        0xff,//ae_dn_switch_ad_step_max;
        0xff,//ae_dn_switch_wait_time;
        0x0,//ape_max_diff;    
        0xf00,//ape_drv_signal_max;    
        0x0,//ape_coeff_distance;    
        0x0,//ape_coeff_speed;    
        0x0,//ape_coeff_acceleration;  
        0xfff,//ape_drv_manual_value;  
        0x800,//ape_damp_manual_value; 
    },
//awb
	{
        1,//awb_d65_en; 
        1,//awb_ccm_en; 
        1,//awb_en;     
        AWB_AUTO,//awb_mode_sel;
        AWB_FULL_IMG,//awb_hist_mode_sel;
        0,//awb_veri_en;      
        AWB_THROUGH_MODE,//awb_fb_en;
        0,//awb_value_save_en;
        1,//awb_ccm_adp_adjust_en;
        1,//awb_stab_en; 
        0x204,//awb_d65_red_gain;
        0x1e8,//awb_d65_blue_gain;
        {
            0x160,//ccm_coff[0][0];
            0x60,//ccm_coff[0][1];
            0x04,//ccm_coff[0][2];
            0x64,//ccm_coff[1][0];
            0x1a0,//ccm_coff[1][1];
            0x40,//ccm_coff[1][2];
            0x4,//ccm_coff[2][0];
            0x40,//ccm_coff[2][1];
            0x144,//ccm_coff[2][2];
        },//ccm_coff[3][3];
        0x104,//ccm_correct_coff;
        {
            0x0,//v_start;
            0x0,//h_start;
            HEIGHT-1,//v_end;
            WIDTH-1,//h_end;	            
        },//awb_win_size; 
        0x20,//awb_correct_diff_th;     
        0x08,//awb_color_changeres_time;
        0x40,//awb_historgram_th;
        0x100,//awb_red_gain_adjust;     
        0x100,//awb_green_gain_adjust;   
        0x100,//awb_blue_gain_adjust;    
        0x200,//awb_red_max_value;
        0x3ff,//awb_blue_max_value;      
        0x40,//awb_red_min_value;       
        0x80,//awb_blue_min_value;
        0x120,//awb_red_obj_value;
        0x120,//awb_blue_obj_value;
    },
//wdr
	{
        0,//wdr_fusion_en;      
        WDR_L_EX_OUT,//wdr_frame_sel;      
        0,//wdr_adp_adjust_en;  
        0,//wdr_stab_en;
        0,//wdr_en;             
        0,//wdr_ghost_remove_en; 
        0,//wdr_3frame_out_mode;
        0,//wdr_mode_sel;
        WDR_EX_RATIO_16F,//wdr_2frame_ex_ratio;
        WDR_EX_RATIO_16_4,//wdr_3frame_ex_ratio; 
        WDR_M_EC_FRAME,//wdr_stat_img_sel;   
        1,//wdr_ltm_data_sel;
        1,//wdr_tz_data_sel;
        0,//wdr_remove_purple_en;
        0x180,//wdr_over_ex_ratio_th1;
        0x20,//wdr_over_ex_ratio_th2;
        0xc0,//wdr_fusion_ratio_th;
        0x40,//wdr_fusion_value1;  
        0x10,//wdr_fusion_value2;
    },
//csc
	{
        {
            0x99,//csc_r2y[0][0]
            0x13b,//csc_r2y[0][1]
            0x4b,//csc_r2y[0][2]
            0x12d,//csc_r2y[1][0]
            0x108,//csc_r2y[1][1]
            0x94,//csc_r2y[1][2]
            0x3a,//csc_r2y[2][0]
            0x33,//csc_r2y[2][1]
            0xdf,//csc_r2y[2][2]
        },// csc_r2y[3][3]
    },
//ada
	{
        1,//ada_rgb_gamma_en; 
        1,//ada_yuv_gamma_en; 
        1,//ada_adjust_en;    
        1,//ada_img_stab_en;
        1,//ada_ccr_en;       
        0,//ada_adp_en;       
        1,//ada_adp_ccr_en;  

        0,//ada_stat_mode_sel;
        0x0,//ada_enh_mode_sel;
        0x40,//ada_stat_max_value; 
        0x40,//ada_ad_stren_max_value;
        {
            0x0,//v_start;
            0x0,//h_start;
            HEIGHT-1,//v_end;
            WIDTH-1,//h_end;	            
        },//aada_win_size;
    },
//rgbir
	{
        1,//rgbir_en;        
        0,//rgbir_rtf_en;    
        0,//rgbir_rpc_en;    
        0,//rgbir_fusion_en;
        0x0,//rgbir_output_sel;
        0x400,//rgbir_rpc_max_value; 
        0x20,//rgbir_rpc_color_coff;
        0x66,//rgbir_rpc_luma_coff; 
        0x100,//rgbir_rpc_th;       
        0x100,//rgbir_rpc_th1;  
    },
//nr2d
	{
        1,//d2nr_pcf_en;       
        1,//d2nr_raw_en;       
        1,//d2nr_edge_en;      
        1,//d2nr_bap_en;       
        1,//d2nr_luma_en;      
        1,//d2nr_chroma_en;    
        1,//d2nr_pcf_adp_en;   
        1,//d2nr_raw_adp_en;   
        1,//d2nr_luma_adp_en;  
        1,//d2nr_chroma_adp_en;
        0x80,//d2nr_raw_intensity;
        0x1ff,//d2nr_bap_intensity;
        0x300,//d2nr_edge_intensity;
        0x80,//d2nr_luma_intensity;
        0x80,//d2nr_chroma_intensity;
    },
//nr3d
	{
        0,//d3nr_en;            
        0,//d3nr_pre_luma_en;  
        0,//d3nr_pre_chroma_en; 
        0,//d3nr_main_luma_en;
        0,//d3nr_main_chroma_en;
        0,//d3nr_post_luma_en;  
        0,//d3nr_post_chroma_en;
        0,//d3nr_2d_luma_en;
        0,//d3nr_2d_chroma_en;  
        0,//d3nr_wb_en;         
        0,//d3nr_wb_sel;
        0,//d3nr_adp_luma_en;
        0,//d3nr_adp_chroma_en;

        0x40,//d3nr_pre_luma_th;        
        0x40,//d3nr_pre_luma_intensity;   
        0x20,//d3nr_pre_chroma_intensity;

        0x80,//d3nr_mid_filter_th;
        0x8,//d3nr_pre_mid_filter_th;    
        0x80,//d3nr_cur_mid_filter_th;    
        0x80,//d3nr_low_pass_filter_th;
        0x40,//d3nr_luma_th;             
        0x0,//d3nr_min_value;
        0x80,//d3nr_luma_intensity;

        0x80,//d3nr_chroma_intensity;    
        0x40,//d3nr_post_edge_th;        
        0x40,//d3nr_post_luma_intensity;  
        0x10,//d3nr_post_chroma_intensity;
    },
//enh
	{
        1,//enh_ltm_en;      
        1,//enh_sharp_en;    
        0,//enh_cc_en;       
        0,//enh_adp_ltm_en;
        1,//enh_adp_sharp_en;
        1,//enh_adp_cc_en; 

        0xc0,//ltm_gain;  
        0x80,//ltm_th;    
        0x08,//enh_nr_th; 
        0x80,//enh_th1;
        0x100,//enh_th2;
        0xc0,//sharp_gain; 
    },
//post ctrl
	{
        1,//post_cont_ad_en;  
        1,//post_luma_ad_en;  
        1,//post_satu_ad_en;  
        0x80,//cont_ad_intensity;
        0x80,//luma_ad_intensity;
        0x80,//satu_ad_intensity;
    },
//otc
	{
        1,//post_otc_en;  
        OTC_Y_MSB_C_LSB,//otc_yc_sel;       
        OTC_VU,//otc_uv_format_sel;
        OTC_POSITIVE,//otc_hsync_pol_sel;
        OTC_POSITIVE,//otc_vsync_pol_sel;
        {
            0x0,//Width_st;
            0x0,//Height_st;
            WIDTH-1,//Width;
            HEIGHT-1,//Height;	            
        },//otc_out_size; 	 
    },
//ldc
	{
        0,//ldc_en;     
        0,//ldc_arith_en;   
        0x90,//ldc_req_freq;   
        0x21c,//ldc_stt_ln;
        WIDTH/2,//ldc_h_center_pos;1920/2
        HEIGHT/2,//ldc_v_center_pos;1080/2
        0x2ac,//ldc_rectify_cr; 
        0x2ac,//ldc_rectify_cz; 
    },
//af
	{
        1,//af_stat_en;      
        AF_FULL_IMG,//af_stat_mode_sel;
        {
            0,//v_start;
            0,//h_start;
            WIDTH-1,//v_end;
            HEIGHT-1,//h_end;	            
        },//af_win_size; 
    },
};
//DS
struct _ISP_DS_CFG_INFO jfx23s_ds_info=
{
    {
        WIDTH,//Width;
        HEIGHT,//Height;
    },//dsInSizeInfo;
    {
        0x00000132,//rgb2yuv_coeff[0][0]
        0x00000259,//rgb2yuv_coeff[0][1]
        0x00000075,//rgb2yuv_coeff[0][2]
        0x00000000,//rgb2yuv_coeff[0][3]
        0x00000f50,//rgb2yuv_coeff[1][0]
        0x00000ea5,//rgb2yuv_coeff[1][1]
        0x0000020b,//rgb2yuv_coeff[1][2]
        0x00000080,//rgb2yuv_coeff[1][3]
        0x0000020b,//rgb2yuv_coeff[2][0]
        0x00000e4a,//rgb2yuv_coeff[2][1]
        0x00000fab,//rgb2yuv_coeff[2][2]
        0x00000080,//rgb2yuv_coeff[2][3]
    },//osd_rgb2yuv_coeff[3][4];
    {
        0x00000400,//yuv2rgb_coeff[0][0]
        0x00000000,//yuv2rgb_coeff[0][1]
        0x000005a1,//yuv2rgb_coeff[0][2]
        0x00000f4c,//yuv2rgb_coeff[0][3]
        0x00000400,//yuv2rgb_coeff[1][0]
        0x00000e9e,//yuv2rgb_coeff[1][1]
        0x00000d22,//yuv2rgb_coeff[1][2]
        0x00000088,//yuv2rgb_coeff[1][3]
        0x00000400,//yuv2rgb_coeff[2][0]
        0x0000071e,//yuv2rgb_coeff[2][1]
        0x00000000,//yuv2rgb_coeff[2][2]
        0x00000f1c,//yuv2rgb_coeff[2][3]
    },//osd_yuv2rgb_coeff[3][4];
    {
        {
            0,//scale_en;
            0,//vscale_filter_en;
            0,//hscale_filter_en;
            1080,//ds_out_size.width;
            720,//ds_out_size.height;
            0,//out_rgb_mode;
            0,//out_rgb_en;  
            0,//out_yuv_mode;
            0,//out_uv_swap;
            {
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
            },// osdInfo[0]
        },//ds0
        {
            0,//scale_en;
            0,//vscale_filter_en;
            0,//hscale_filter_en;
            1080,//ds_out_size.width;
            720,//ds_out_size.height;
            0,//out_rgb_mode;
            0,//out_rgb_en;  
            0,//out_yuv_mode;
            0,//out_uv_swap;
            {
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
            },// osdInfo[0]
        },//ds1
        {
            0,//scale_en;
            0,//vscale_filter_en;
            0,//hscale_filter_en;
            1080,//ds_out_size.width;
            720,//ds_out_size.height;
            0,//out_rgb_mode;
            1,//out_rgb_en;  
            0,//out_yuv_mode;
            0,//out_uv_swap;
            {
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
//
                0,//osd_enable;
                0,//osd_type;      
                0,//osd_alpha_tpye;
                320,//osd_size.width;
                240,//osd_size.Height;
                0x30000000,//osd_rgb_addr[0]; 
                0x30000000,//osd_rgb_addr[1];   
                0x30000000,//osd_alpha_addr[0];
                0x30000000,//osd_alpha_addr[1];
                2048,//osd_stride;       
                2048,//osd_alpha_stride; 
                0,//osd_position_win.v_start;
                0,//osd_position_win.h_start;
                240,//osd_position_win.v_end;
                320,//osd_position_win.h_end;	
                0,//osd_dma_request_length;
                0,//osd_dma_map;           
                0,//osd_rgb_rev;           
                0,//osd_global_alpha;      
                0,//osd_swap_64;
                0,//osd_outstanding_num;
                0,//osd_bd_limit_en;
            },// osdInfo[0]
        },//ds2
    },
};
//
#if 0
struct _VO_CORE_INFO_S jfx23s_vo_info =
{
    {

    },//dispInfo;
    {

    },//layer0Info;
    {

    },//layer1Info;
    {

    },//layer2Info;
    {

    },//layer3Info;
    {

    },//osd0Info;
    {

    },//osd1Info;
    {

    },//osd2Info;
    {

    },//S osdRgb2YuvInfo;
    {

    },//yuv2rgbInfo;  
    {

    },//dispMixCtlInfo;
    {

    },//ditherctlen;
    {

    },//clutctlen;
    {

    },//dispIrqInfo;
    {

    },//wbInfo;
};
#endif