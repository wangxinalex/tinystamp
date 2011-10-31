

all:
	cd tinySTM && make all
	cd ..
	cd stamp-0.9.10 && ./storiginal.sh out-tinySTM.stm stm sim 1
	cd ..
clean:
	cd tinySTM && make clean
