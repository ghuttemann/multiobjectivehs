#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/926592557/allocate.o \
	${OBJECTDIR}/_ext/926592557/list.o \
	${OBJECTDIR}/_ext/926592557/problemdef.o \
	${OBJECTDIR}/_ext/926592557/fillnds.o \
	${OBJECTDIR}/_ext/926592557/sort.o \
	${OBJECTDIR}/_ext/926592557/merge.o \
	${OBJECTDIR}/_ext/926592557/report.o \
	${OBJECTDIR}/_ext/926592557/initialize.o \
	${OBJECTDIR}/_ext/926592557/rank.o \
	${OBJECTDIR}/_ext/926592557/crossover.o \
	${OBJECTDIR}/_ext/926592557/eval.o \
	${OBJECTDIR}/_ext/926592557/dominance.o \
	${OBJECTDIR}/_ext/926592557/crowddist.o \
	${OBJECTDIR}/_ext/926592557/mutation.o \
	${OBJECTDIR}/_ext/926592557/rand.o \
	${OBJECTDIR}/_ext/926592557/nsga2r.o \
	${OBJECTDIR}/_ext/926592557/decode.o \
	${OBJECTDIR}/_ext/926592557/auxiliary.o \
	${OBJECTDIR}/_ext/926592557/tourselect.o \
	${OBJECTDIR}/_ext/926592557/display.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsga2_zdt_cec09.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsga2_zdt_cec09.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsga2_zdt_cec09 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/926592557/allocate.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/allocate.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/allocate.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/allocate.c

${OBJECTDIR}/_ext/926592557/list.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/list.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/list.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/list.c

${OBJECTDIR}/_ext/926592557/problemdef.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/problemdef.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/problemdef.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/problemdef.c

${OBJECTDIR}/_ext/926592557/fillnds.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/fillnds.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/fillnds.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/fillnds.c

${OBJECTDIR}/_ext/926592557/sort.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/sort.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/sort.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/sort.c

${OBJECTDIR}/_ext/926592557/merge.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/merge.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/merge.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/merge.c

${OBJECTDIR}/_ext/926592557/report.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/report.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/report.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/report.c

${OBJECTDIR}/_ext/926592557/initialize.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/initialize.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/initialize.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/initialize.c

${OBJECTDIR}/_ext/926592557/rank.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/rank.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/rank.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/rank.c

${OBJECTDIR}/_ext/926592557/crossover.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/crossover.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/crossover.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/crossover.c

${OBJECTDIR}/_ext/926592557/eval.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/eval.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/eval.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/eval.c

${OBJECTDIR}/_ext/926592557/dominance.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/dominance.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/dominance.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/dominance.c

${OBJECTDIR}/_ext/926592557/crowddist.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/crowddist.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/crowddist.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/crowddist.c

${OBJECTDIR}/_ext/926592557/mutation.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/mutation.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/mutation.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/mutation.c

${OBJECTDIR}/_ext/926592557/rand.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/rand.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/rand.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/rand.c

${OBJECTDIR}/_ext/926592557/nsga2r.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/nsga2r.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/nsga2r.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/nsga2r.c

${OBJECTDIR}/_ext/926592557/decode.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/decode.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/decode.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/decode.c

${OBJECTDIR}/_ext/926592557/auxiliary.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/auxiliary.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/auxiliary.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/auxiliary.c

${OBJECTDIR}/_ext/926592557/tourselect.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/tourselect.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/tourselect.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/tourselect.c

${OBJECTDIR}/_ext/926592557/display.o: ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/display.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/926592557
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/926592557/display.o ../../hs_vs_nsga2/nsga2_zdt_cec09/nsga2-gnuplot-v1.1.5/display.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nsga2_zdt_cec09.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
