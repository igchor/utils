alias sudo='sudo '
alias pf='LD_PRELOAD=libpmemfile.so PMEMFILE_POOLS=/tmp/pmemfile:/mnt/pmem/pmemfile/pmemfile_pool PMEM_IS_PMEM_FORCE=1'
alias perf_record='perf record -gR'
alias flame='sudo /home/igchor/bin/perf script | ~/Projects/FlameGraph/stackcollapse-perf.pl | ~/Projects/FlameGraph/flamegraph.pl'
alias pmem_conf='PKG_CONFIG_PATH=/home/igchor/libs/nvml-rel/lib/pkgconfig:/home/igchor/libs/syscall_intercept-rel/lib/pkgconfig LD_LIBRARY_PATH=/home/igchor/libs/nvml-rel/lib:/home/igchor/libs/syscall_intercept-rel/lib'
alias tren='trans en:pl'
alias trpl='trans pl:en'
alias clip='xclip -selection clipboard'

