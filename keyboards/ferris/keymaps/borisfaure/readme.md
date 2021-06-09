# License

Copyright 2021 Boris Faure @borisfaure

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Overview

This is a QWERTY-based keymap with some adaptations.  It is written mostly to
run on a Ferris keyboard, a 34-keys keyboard.

The first change is to remove the Z key and place ESC instead.

There are few layers:
* LOWER, activated with the left thumb: acts a symbol layer.  It also has
  PageUp/Down on the home row to ease the navigation.  Some matching symbols
  are close together like the parentheses, the square and curly brackets.
  Pressing the I key does a Shift-Insert.
* RAISE layer, activate with the right thumb is used to easily enter french
  characters and to be able to type the `z` character.  It also features the
  arrow keys under the right homerow (`hjkl`). It also has the CapsLock and
  NumLock keys.
* NUMBERS layer, activated by holding the `N` or `B` keys, or activating
  NumLock.  It features on the left hand a numpad and the Fx keys on the right
  hand.
* MISC layer, activated by holding the `T` or `Y` keys.  It has audio related
  actions on the left hand and mouse control on the right hand.  The thumb
  keys are used to handle mouse clicks.  The keys on the outer right mimic a
  mouse wheel.
* TMUX layer, activated by holding the `F` key.  It is used to ease combos on
  tmux, the terminal multiplexer.

When held, the following keys act as a modifier:

* `Escape` (in place of `Z` on qwerty) is Left Shift, `/` is Right Shift
* `A` is Left Control, `;` is Right Control
* `W` is Left Win, `O` is Right Win
* `X` and `'` are both Left Alt
* Right Alt is Space on the RAISE layer

The four thumbs buttons are used as follows:
* Inner Left is the LOWER layer when held, Tab when tapped
* Outer Left is Space
* Outer Right is Enter
* Inner Right is the RAISE layer when held, Backspace when tapped
