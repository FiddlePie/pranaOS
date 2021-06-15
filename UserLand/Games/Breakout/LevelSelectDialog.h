/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

// includes
#include <LibGUI/Dialog.h>

namespace Breakout {
class LevelSelectDialog : public GUI::Dialog {
    C_OBJECT(LevelSelectDialog)

public:
    virtual ~LevelSelectDialog() override;
    static int show(int& board_number, Window* parent_window);
    int level() const { return m_level; }
    
}

}