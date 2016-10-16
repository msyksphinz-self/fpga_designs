*************************************************************************
   ____  ____ 
  /   /\/   / 
 /___/  \  /   
 \   \   \/    © Copyright 2016 Xilinx, Inc. All rights reserved.
  \   \        This file contains confidential and proprietary 
  /   /        information of Xilinx, Inc. and is protected under U.S. 
 /___/   /\    and international copyright and other intellectual 
 \   \  /  \   property laws. 
  \___\/\___\ 
 
*************************************************************************

Vendor: Xilinx 
Current readme.txt Version: 1.0.0
Date Last Modified:  11NOV2015
Date Created: 11Nov2015

Associated Filename: xapp1170-zynq-hls.pdf
Associated Document: XAPP1170, Zynq-7000 All Programmable SoC Accelerator for Floating Point Multiplication using Vivado HLS

Supported Device(s): Zynq-7000 Series devices 
*************************************************************************

Disclaimer: 

      This disclaimer is not a license and does not grant any rights to 
      the materials distributed herewith. Except as otherwise provided in 
      a valid license issued to you by Xilinx, and to the maximum extent 
      permitted by applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE 
      "AS IS" AND WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL 
      WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
      INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
      NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and 
      (2) Xilinx shall not be liable (whether in contract or tort, 
      including negligence, or under any other theory of liability) for 
      any loss or damage of any kind or nature related to, arising under 
      or in connection with these materials, including for any direct, or 
      any indirect, special, incidental, or consequential loss or damage 
      (including loss of data, profits, goodwill, or any type of loss or 
      damage suffered as a result of any action brought by a third party) 
      even if such damage or loss was reasonably foreseeable or Xilinx 
      had been advised of the possibility of the same.

Critical Applications:

      Xilinx products are not designed or intended to be fail-safe, or 
      for use in any application requiring fail-safe performance, such as 
      life-support or safety devices or systems, Class III medical 
      devices, nuclear facilities, applications related to the deployment 
      of airbags, or any other applications that could lead to death, 
      personal injury, or severe property or environmental damage 
      (individually and collectively, "Critical Applications"). Customer 
      assumes the sole risk and liability of any use of Xilinx products 
      in Critical Applications, subject only to applicable laws and 
      regulations governing limitations on product liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS 
FILE AT ALL TIMES.

*************************************************************************

This readme file contains these sections:

1. REVISION HISTORY
2. OVERVIEW
3. SOFTWARE TOOLS AND SYSTEM REQUIREMENTS
4. DESIGN FILE HIERARCHY
5. INSTALLATION AND OPERATING INSTRUCTIONS
6. OTHER INFORMATION (OPTIONAL)
7. SUPPORT


1. REVISION HISTORY 

<Describe changes to the reference design ZIP file using this format>

            Readme  
Date        Version      Revision Description
=========================================================================
11NOV2015   1.0          Initial Xilinx release.
=========================================================================

2. OVERVIEW

This readme describes how to use the files that come with XAPP1170.

This application note includes an example design, which is explained
in detail within the application note. The example designs consists
of two projects:

- Vivado HLS source files, which is use to synthesize, simulate and export
the IP core described in the application note.

- A Vivado project, which can be used to demonstrate the functionality 
of the design on a Xilinx ZC702 development board.

In order to facilitate exploration of the design a TCL script is provided
which simulates, synthesizes, co-simulates and exports the HLS source code.
This TCL script is called run_hls._script.tcl and can be found in the accompanying
zip file. The script can be executed by typing:

vivado_hls -f run_hls_script.tcl 

The Vivado project can be opened with Vivado 2015.4 and already includes
an instance of the IP generated from the Vivado HLS project, it is thus ready
to synthesize and implement. The resulting bitstream can be deployed to a
Xilinx ZC702 development boad. 

NOTE: If you decompress the files in Windows and receive a message that the path name for some files is too long, cancel and re-try the decompression into a location with a shorter path name (such a directly onto your C:\ drive).

3. SOFTWARE TOOLS AND SYSTEM REQUIREMENTS

* Xilinx Vivado HLS 2015.2 or higher
* Xilinx Vivado 2015.2 or higher

4. DESIGN FILE HIERARCHY

<Describe the file hierarchy by type (HDL files, simulation files, etc.)>

The directory structure underneath this top-level folder is described 
below:

\xapp1170
  |
  |
  +-----	\pre_built
  |			Contains the complete built project in Vivado, Vivado HLS and SDK
  |
  +-----	\empty
  |			Contains the empty project to be built with the related TCL scripts


In particular, both subfolders are organized as follows: 

\pre_build
 | 
 |
 +-----	\hls
 |		Contains the source file for the Vivado HLS example design
 |
 |			+--\ip
 |				Contains the IP core to be exported to the Vivado project 
 |
 +-----	\vivado
 |       This folder contains project files for the ZC702 board, including the SDK workspace.
 |       
 |		    +--\vivado_ip_repo
 |				Contains the IP core generated by Vivado HLS and imported into this Vivado project 
 +-----	\arm_sw
 |       This folder contains the user's application software to be imported into the Xilinx SDK 

 
 In the xapp1170/empty/vivado sub-folder, the Vivado IP Integrator block design can be generated by 
 typing the TCL command in the Vivado TCL console:
 
 source v2015_3_ipi_xapp1170_bd.tcl
 
 
 
5. INSTALLATION AND OPERATING INSTRUCTIONS 

To run the included design you need to:

1) Install the Xilinx Vivado 2015.2 or later tools.
2) Download and extract the attached archive into a folder.
3) In order to test, synthesize and export the Vivado HLS source code,
   navigate to the vivado_hls subfolder and execute the run_hls_script.tcl
   script provided. Note that Vivado HLS 2015.3 might generate less optimized 
   RTL code in comparison with HLS 2015.2 or HLS 2015.4.
4) To implement the vivado example design and download the bitstream
   on a ZC702 board, open the provided project found in the vivado 
   sub-folder with Vivado, implement the provided design and download
   the bitstream to an FPGA.

6. SUPPORT

To obtain technical support for this reference design, go to 
www.xilinx.com/support to locate answers to known issues in the Xilinx
Answers Database or to create a WebCase.  