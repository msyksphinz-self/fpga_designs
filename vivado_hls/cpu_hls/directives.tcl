# set_directive_pipeline -II 8 "cpu_hls/L0"

set_directive_interface -mode m_axi -bundle mst0 "cpu_hls"
set_directive_interface -mode m_axi -bundle mst0 "cpu_hls" mem
