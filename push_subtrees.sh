#!/bin/bash

# Before pushing commit all changes to main project and push it to remote location
git subtree push -P platform/aoaa_board aoaa_board master
git subtree push -P platform/cmsis_core_lpc17xx cmsis_core_lpc17xx master
git subtree push -P platform/cmsis_dsp cmsis_dsp master
git subtree push -P platform/common common master
git subtree push -P platform/freertos freertos master
git subtree push -P platform/lpc17xx lpc17xx master
git subtree push -P platform/lwip lwip master
git subtree push -P toolchain/make make master

# git subtree pull -P platform/aoaa_board aoaa_board master
# git subtree pull -P platform/cmsis_core_lpc17xx cmsis_core_lpc17xx master
# git subtree pull -P platform/cmsis_dsp cmsis_dsp master
# git subtree pull -P platform/common common master
# git subtree pull -P platform/freertos freertos master
# git subtree pull -P platform/lpc17xx lpc17xx master
# git subtree pull -P platform/lwip lwip master
# git subtree pull -P toolchain/make make master

# git push aoaa_board `git subtree split --prefix platform/aoaa_board master`:master --force
# git push cmsis_core_lpc17xx `git subtree split --prefix platform/cmsis_core_lpc17xx master`:master --force
# git push cmsis_dsp `git subtree split --prefix platform/cmsis_dsp master`:master --force
# git push common `git subtree split --prefix platform/common master`:master --force
# git push freertos `git subtree split --prefix platform/freertos master`:master --force
# git push lpc17xx `git subtree split --prefix platform/lpc17xx master`:master --force
# git push lwip `git subtree split --prefix platform/lwip master`:master --force
# git push make `git subtree split --prefix toolchain/make master`:master --force

# git subtree split --rejoin -P platform/aoaa_board
# git subtree split --rejoin -P platform/cmsis_core_lpc17xx
# git subtree split --rejoin -P platform/cmsis_dsp
# git subtree split --rejoin -P platform/common
# git subtree split --rejoin -P platform/freertos
# git subtree split --rejoin -P platform/lpc17xx
# git subtree split --rejoin -P platform/lwip
# git subtree split --rejoin -P toolchain/make