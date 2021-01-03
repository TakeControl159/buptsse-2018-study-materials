# makefile for System: SelectiveARQ

sctAUTOCFGDEP =
sctCOMPFLAGS = -DXUSE_GENERIC_FUNC

!include $(SCTDIR)\make.opt

default: SelectiveARQ$(sctEXTENSION)

SelectiveARQ$(sctEXTENSION): \
  SelectiveARQ$(sctOEXTENSION) \
  $(sctLINKKERNELDEP)
	$(sctLD) @<<
	$(sctLDFLAGS)
	 SelectiveARQ$(sctOEXTENSION) $(sctLINKKERNEL)
	/OUT:SelectiveARQ$(sctEXTENSION)
<<

SelectiveARQ$(sctOEXTENSION): \
  SelectiveARQ.c
	$(sctCC) @<<
	$(sctCPPFLAGS) $(sctCCFLAGS)
	$(sctIFDEF)
	/FoSelectiveARQ$(sctOEXTENSION)
	SelectiveARQ.c
<<
