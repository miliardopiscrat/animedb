animedb
=======

Anime scraper for realtek based media players.

It's a cli cross-platform aplication for scraping animes and cartoons. 

(cygwin, linux x86, realtek mipsel toolchain)

Scraper works in two modes, first mode is an id finder for given phrase. Second option is download description of given 
movie.

CLI options:

-[option] [parameter]

options:

[s]               - switch mode to id finder 
[k] [parameter]   - keyword parameter for given mode. For id search mode is phrase. For description download mode is id  
                    from db.
[o] [path]        - path for output file
[l] [pl|en]       - language mode (not used yet)

example usage:


search for phrase gundam in db:

./animedb -s -k gundam -o /tmp/out.xml

download description for movie with id 8566

./animedb -k 8566 -o /tmp/movie.descr.xml

=====

CI builds can be found here: https://circleci.com/gh/miliardopiscrat/animedb
