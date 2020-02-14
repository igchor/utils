 git show HEAD --name-only | tail -n +7 | head -n1 | xargs sed -E 's/Copyright ([0-9]*)-[0-9]*/Copyright \1-2020/'
