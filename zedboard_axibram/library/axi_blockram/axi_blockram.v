// ***************************************************************************
// ***************************************************************************
// Copyright 2011(c) Analog Devices, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//     - Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     - Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in
//       the documentation and/or other materials provided with the
//       distribution.
//     - Neither the name of Analog Devices, Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//     - The use of this software may or may not infringe the patent rights
//       of one or more patent holders.  This license does not release you
//       from the requirement that you obtain separate licenses from these
//       patent holders to use this software.
//     - Use of the software either in source or binary form, must be run
//       on or directly connected to an Analog Devices Inc. component.
//
// THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED.
//
// IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, INTELLECTUAL PROPERTY
// RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ***************************************************************************
// ***************************************************************************
// software programmable clock generator (still needs a reference input!)

module axi_blockram
  (
  input wire         clk,
  input wire         clk2,
  output wire        clk_0,
  output wire        clk_1,

  // axi interface

  input wire         s_axi_aclk,
  input wire         s_axi_aresetn,
  input wire         s_axi_awvalid,
  input wire [31:0]  s_axi_awaddr,
  output wire        s_axi_awready,
  input wire         s_axi_wvalid,
  input wire [31:0]  s_axi_wdata,
  input wire [ 3:0]  s_axi_wstrb,
  output wire        s_axi_wready,
  output wire        s_axi_bvalid,
  output wire [ 1:0] s_axi_bresp,
  input wire         s_axi_bready,
  input wire         s_axi_arvalid,
  input wire [31:0]  s_axi_araddr,
  output wire        s_axi_arready,
  output wire        s_axi_rvalid,
  output wire [31:0] s_axi_rdata,
  output wire [ 1:0] s_axi_rresp,
  input wire         s_axi_rready,
  input wire [ 2:0]  s_axi_awprot,
  input wire [ 2:0]  s_axi_arprot
   );

  // parameters

  parameter   ID = 0;
  parameter   DEVICE_TYPE = 0;
  parameter   CLKIN_PERIOD  = 5.0;
  parameter   CLKIN2_PERIOD  = 5.0;
  parameter   VCO_DIV = 11;
  parameter   VCO_MUL = 49;
  parameter   CLK0_DIV = 6;
  parameter   CLK0_PHASE = 0.000;
  parameter   CLK1_DIV = 6;
  parameter   CLK1_PHASE = 0.000;
  parameter   CLK2_DIV = 6;
  parameter   CLK2_PHASE = 0.000;

  // clocks

  // reset and clocks

  wire              up_wreq_s;
  wire [13: 0]      up_waddr_s;
  wire [31: 0]      up_wdata_s;
  wire              up_wack_s;
  wire              up_rreq_s;
  wire [13: 0]      up_raddr_s;
  reg [31: 0]      up_rdata_s;
  reg              up_rack_s;


  // signal name changes

  assign up_clk = s_axi_aclk;
  assign up_rstn = s_axi_aresetn;

  up_axi i_up_axi
    (
    .up_rstn (up_rstn),
    .up_clk  (up_clk),
    .up_axi_awvalid (s_axi_awvalid),
    .up_axi_awaddr  (s_axi_awaddr),
    .up_axi_awready (s_axi_awready),
    .up_axi_wvalid  (s_axi_wvalid),
    .up_axi_wdata   (s_axi_wdata),
    .up_axi_wstrb   (s_axi_wstrb),
    .up_axi_wready  (s_axi_wready),
    .up_axi_bvalid  (s_axi_bvalid),
    .up_axi_bresp   (s_axi_bresp),
    .up_axi_bready  (s_axi_bready),
    .up_axi_arvalid (s_axi_arvalid),
    .up_axi_araddr  (s_axi_araddr),
    .up_axi_arready (s_axi_arready),
    .up_axi_rvalid  (s_axi_rvalid),
    .up_axi_rresp   (s_axi_rresp),
    .up_axi_rdata   (s_axi_rdata),
    .up_axi_rready  (s_axi_rready),
    .up_wreq  (up_wreq_s),
    .up_waddr (up_waddr_s),
    .up_wdata (up_wdata_s),
    .up_wack  (up_wack_s),
    .up_rreq  (up_rreq_s),
    .up_raddr (up_raddr_s),
    .up_rdata (up_rdata_s),
    .up_rack  (up_rack_s));

  reg [31: 0]     reg_mem [1023: 0];

  assign up_wack_s = 1'b1;

  always @ (posedge clk) begin
    if (up_wreq_s) begin
      reg_mem[up_waddr_s[9:0]] <= up_wdata_s[31: 0];
    end
  end

  always @ (posedge clk) begin
    up_rack_s  <= up_rreq_s;
    up_rdata_s <= reg_mem[up_raddr_s[9:0]];
  end

endmodule

// ***************************************************************************
// ***************************************************************************
