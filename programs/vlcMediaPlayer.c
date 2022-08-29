#include <stdio.h>
#include <stdlib.h>
#include <vlc/vlc.h>
#include <unistd.h>
#include <string.h>

bool is_remote_url(const char *url)
{
  return strstr(url, "://") != NULL;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  libvlc_instance_t *inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;

  // Load vlc engine
  inst = libvlc_new(0, NULL);
  if (!inst)
  {
    fprintf(stderr, "Failed to load vlc engine\n");
    return EXIT_FAILURE;
  }

  // create a new item
  // if argv[1] is a remote file, use libvlc_media_new_location() instead

  if (is_remote_url(argv[1]))
  {
    m = libvlc_media_new_location(inst, argv[1]);
  }
  else
  {
    m = libvlc_media_new_path(inst, argv[1]);
  }

  // create a media player playing environment
  mp = libvlc_media_player_new_from_media(m);

  // no need to keep using media
  libvlc_media_release(m);

  // play the media player
  libvlc_media_player_play(mp);
  sleep(2);

  // play until end of file
  while (libvlc_media_player_is_playing(mp))
  {
    sleep(0.1);
  }

  // stop playing
  libvlc_media_player_stop(mp);

  // free the media player
  libvlc_media_release(m);

  libvlc_release(inst);

  return EXIT_SUCCESS;
}