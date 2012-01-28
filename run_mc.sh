#!/bin/sh

#############################################################################

cp core/include/mc_THiggsD3PD_GSF.h core/include/THiggsD3PD.h

#############################################################################

SRCS=\
config.txt\
core/main.cc,\
core/core.cc,\
core/config.cc,\
core/loader.cc,\
core/utils.cc,\
core/include/core.h,\
core/include/THiggsD3PD.h,\
core/include/athena/egammaPIDdefs.h,\
analysis/ilumicalc_period_BD_Atlas_Ready.root,\
analysis/ilumicalc_period_EH_Atlas_Ready.root,\
analysis/ilumicalc_period_IK_Atlas_Ready.root,\
analysis/ilumicalc_period_LM_Atlas_Ready.root,\
analysis/Mu_MC11bprime_analysis.root,\
analysis/higgs_analysis/main.h,\
analysis/higgs_analysis/main.cc,\
analysis/higgs_analysis/utils.h,\
analysis/higgs_analysis/utils.cc,\
analysis/higgs_analysis/triggers.cc,\
analysis/higgs_analysis/Z_analysis.cc,\
analysis/higgs_analysis/H_analysis.cc

#############################################################################

prun --exec "higgs_analysis --grid=prun --enable-ER --enable-SM --EL_USE_LOOSE=1 -o output.root \ %IN" --bexec "make ALL" \
--athenaTag=17.0.4 \
--inDS $1 \
--outDS $2 \
--extFile $SRCS \
--outputs output.root

#############################################################################

exit $?

#############################################################################

