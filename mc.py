#!/usr/bin/env python

#############################################################################

import time, getpass, commands

#############################################################################

L = [
	'mc11_7TeV.107650.AlpgenJimmyZeeNp0_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107651.AlpgenJimmyZeeNp1_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107652.AlpgenJimmyZeeNp2_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107653.AlpgenJimmyZeeNp3_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107654.AlpgenJimmyZeeNp4_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107655.AlpgenJimmyZeeNp5_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107660.AlpgenJimmyZmumuNp0_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107661.AlpgenJimmyZmumuNp1_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107662.AlpgenJimmyZmumuNp2_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107663.AlpgenJimmyZmumuNp3_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107664.AlpgenJimmyZmumuNp4_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107665.AlpgenJimmyZmumuNp5_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107670.AlpgenJimmyZtautauNp0_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107671.AlpgenJimmyZtautauNp1_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107672.AlpgenJimmyZtautauNp2_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107673.AlpgenJimmyZtautauNp3_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107674.AlpgenJimmyZtautauNp4_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',
	'mc11_7TeV.107675.AlpgenJimmyZtautauNp5_pt20.merge.NTUP_HSG2.e835_s1299_s1300_r2820_r2872_p768/',

	'mc11_7TeV.116960.AlpgenHWfZeebbNp0_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116961.AlpgenHWfZeebbNp1_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116962.AlpgenHWfZeebbNp2_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116963.AlpgenHWfZeebbNp3_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116965.AlpgenHWfZmumubbNp0_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116966.AlpgenHWfZmumubbNp1_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116967.AlpgenHWfZmumubbNp2_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116968.AlpgenHWfZmumubbNp3_4LepM.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',

	'mc11_7TeV.116950.AlpgenHWfZeebbNp0_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116951.AlpgenHWfZeebbNp1_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116952.AlpgenHWfZeebbNp2_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116953.AlpgenHWfZeebbNp3_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116955.AlpgenHWfZmumubbNp0_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116956.AlpgenHWfZmumubbNp1_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116957.AlpgenHWfZmumubbNp2_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.116958.AlpgenHWfZmumubbNp3_Veto4LepM_Pass3Lep.merge.NTUP_HSG2.e835_s1310_s1300_r2820_r2872_p768/',

	'mc11_7TeV.105200.T1_McAtNlo_Jimmy.merge.NTUP_HSG2.e835_s1272_s1274_r2820_r2872_p768/',
	'mc11_7TeV.109345.T1_McAtNlo_Jimmy_2LeptonsMll60GeV.merge.NTUP_HSG2.e961_s1310_s1300_r2820_r2872_p768/',
	'mc11_7TeV.109346.T1_McAtNlo_Jimmy_4LepMass_Mll60GeV12GeV.merge.NTUP_HSG2.e961_s1310_s1300_r2820_r2872_p768/',

	'mc11_7TeV.109292.Pythiazz4l_3MultiLeptonFilterElecMu.merge.NTUP_HSG2.e825_s1310_s1300_r2820_r2872_p768/',
]

#############################################################################

VERSION = int(time.time())

#############################################################################

for in_ds in L:

	out_ds = 'user.%s.%s.%s-%d_%s' % (getpass.getuser(), in_ds.split('.')[+1], in_ds.split('.')[+2], VERSION, in_ds.split('.')[-1])

	print('Running \'%s\' -> \'%s\'...' % (in_ds, out_ds))

	status, output = commands.getstatusoutput('./run_mc.sh %s %s' % (in_ds, out_ds))

	if status == 0:
		print('[ \033[32m Ok. \033[0m ]')
	else:
		print('[ \033[31mError\033[0m ]')

		print('\033[31m%s\033[0m' % output)

#############################################################################

