all: $(EXEC)

CFLAGS = -Wall -std=c++11 -O3 
HEADER += hash.h util.h bitmap.h datatypes.hpp adaptor.hpp discounter_lc.hpp discounter_km.hpp discounter_hll.hpp 
SRC += hash.c adaptor.cpp bitmap.c discounter_lc.cpp discounter_km.cpp discounter_hll.cpp 

LIBS= -lpcap -lm

main_lc: main_lc.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

lc_attack: lc_attack_test.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)


lc_error_test: lc_error_test.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

lc_bt: lc_bt.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

lc_bt_improve: lc_bt_improve.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

lc_flat_s1: lc_flat_s1.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

lc_deflat: lc_deflat.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

main_hll: main_hll.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

hll_infer_m: hll_infer_m.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

hll_deflation_s1_v1: hll_deflation_s1_v1.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)


hll_deflation_s1_v2: hll_deflation_s1_v2.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

hll_inflation: hll_inflation.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

hll_inflation2: hll_inflation2.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)


hll_deflation: hll_deflation.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

main_km: main_km.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_inflation: km_inflation.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_inflation2: km_inflation2.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_inflation3: km_inflation3.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_attack: kmv_attack_test.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_deflation: km_deflation.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_deflation2: km_deflation2.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_deflation_s2: km_deflation_s2.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)

km_infer_k:km_infer_k.cpp $(SRC) $(HEADER) 
	g++ $(CFLAGS) $(INCLUDES) -o $@ $< $(SRC) $(LIBS)


clean:
	rm -rf $(EXEC)
	rm -rf *log*
	rm -rf *out*
