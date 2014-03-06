MATLAB="/usr/local/matlab2013b"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/dmabeywa/.matlab/R2013b"
OPTSFILE_NAME="./mexopts.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for quad_8state_kalman_sil" > quad_8state_kalman_sil_mex.mki
echo "CC=$CC" >> quad_8state_kalman_sil_mex.mki
echo "CFLAGS=$CFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "CLIBS=$CLIBS" >> quad_8state_kalman_sil_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "CXX=$CXX" >> quad_8state_kalman_sil_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "CXXLIBS=$CXXLIBS" >> quad_8state_kalman_sil_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "LD=$LD" >> quad_8state_kalman_sil_mex.mki
echo "LDFLAGS=$LDFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> quad_8state_kalman_sil_mex.mki
echo "Arch=$Arch" >> quad_8state_kalman_sil_mex.mki
echo OMPFLAGS= >> quad_8state_kalman_sil_mex.mki
echo OMPLINKFLAGS= >> quad_8state_kalman_sil_mex.mki
echo "EMC_COMPILER=" >> quad_8state_kalman_sil_mex.mki
echo "EMC_CONFIG=optim" >> quad_8state_kalman_sil_mex.mki
"/usr/local/matlab2013b/bin/glnxa64/gmake" -B -f quad_8state_kalman_sil_mex.mk
