set_param project.enableReportConfiguration 0
load_feature core
current_fileset
xsim {idct} -view {{idct_dataflow_ana.wcfg}} -tclbatch {idct.tcl} -protoinst {idct.protoinst}
