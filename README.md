# builin.c
- do_cd()
- cd_change_dir() //called from do_cd
- do_pwd()
- do_echo() //testing needed

# libft
- added strcmp.c

# arena_mg.c
- added aditional checking to arena_expand_mg();

# minishell.h

```bash
- # include "libft.h"
- # include <linux/limits.h>
- # include <limits.h>

- # ifndef SIZE_MAX
- # define SIZE_MAX ((size_t)-1)
- # endif

- # manually defined SIZE_MAX bcs limits.h and    linux/limits.h seams doesnt work : 
```
# colors.h 
- include in minishell.h

# sig_hand.h 
- added for handling signals

# src/signals.c
- setup_sig_handler()