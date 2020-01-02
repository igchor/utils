alias c++_tmpl_filt_='sed "s/<[^<>]*>/{}/g"'
alias c++_tmpl_filt='c++_tmpl_filt_ | c++_tmpl_filt_ | c++_tmpl_filt_ | c++_tmpl_filt_ | c++_tmpl_filt_ | c++_tmpl_filt_ | c++_tmpl_filt_ | sed "s/{}/<>/g"'
