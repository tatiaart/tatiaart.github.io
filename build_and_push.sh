#!/usr/bash

site_dir="${PWD}"
jekyll build
tmp_dir=$(mktemp -d -t site-build-XXXX)
cd "$tmp_dir" || exit
git clone git@github.com:tatiaart/tatiaart.github.io.git
cd tatiaart.github.io || exit
git branch gh-pages
git checkout gh-pages
mv "$tmp_dir/tatiaart.github.io/.git" "$tmp_dir/.git"
rm -rf "$tmp_dir/tatiaart.github.io"
cp -r "$site_dir/_site" "$tmp_dir/tatiaart.github.io"
mv "$tmp_dir/.git" "$tmp_dir/tatiaart.github.io/.git"
cd "$tmp_dir/tatiaart.github.io" || exit
git add -A
git commit -m "$(date +"%s")"
ssh-agent sh -c 'ssh-add ~/.ssh/tatiaart.key; git push'
cd "$site_dir" || exit
rm -rf "$tmp_dir"
echo "done"