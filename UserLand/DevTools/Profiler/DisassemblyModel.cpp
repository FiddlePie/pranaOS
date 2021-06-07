/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */


// includes
#include "DisassemblyModel.h"
#include "Profile.h"
#include <AK/MappedFile.h>
#include <LibELF/Image.h>
#include <LibGUI/Painter.h>
#include <LibX86/Disassembler.h>
#include <LibX86/ELFSymbolProvider.h>
#include <ctype.h>
#include <stdio.h>

namespace Profiler {

static const Gfx::Bitmap& heat_gradient()
{
    static RefPtr<Gfx::Bitmap> bitmap;
    if (!bitmap) {
        bitmap = Gfx::Bitmap::create(Gfx::BitmapFormat::BGRx8888, { 101, 1 });
        GUI::Painter painter(*bitmap);
        painter.fill_rect_with_gradient(Orientation::Horizontal, bitmap->rect(), Color::from_rgb(0xffc080), Color::from_rgb(0xff3000));
    }
    return *bitmap;
}

static Color color_for_percent(int percent)
{
    VERIFY(percent >= 0 && percent <= 100);
    return heat_gradient().get_pixel(percent, 0);
}

DisassemblyModel::DisassemblyModel(Profile& profile, ProfileNode& node)
    : m_profile(profile)
    , m_node(node)
{
    OwnPtr<ELF::Image> kernel_elf;
    const ELF::Image* elf;
    FlatPtr base_address = 0;
    if (m_node.address() >= 0xc0000000) {
        if (!m_kernel_file) {
            auto file_or_error = MappedFile::map("/boot/Kernel");
            if (file_or_error.is_error())
                return;
            m_kernel_file = file_or_error.release_value();
        }
        kernel_elf = make<ELF::Image>((const u8*)m_kernel_file->data(), m_kernel_file->size());
        elf = kernel_elf.ptr();
    } else {
        auto& process = node.process();
        auto library_data = process.library_metadata.library_containing(node.address());
        if (!library_data) {
            dbgln("no library data for address {:p}", node.address());
            return;
        }
        elf = &library_data->object->elf;
        base_address = library_data->base;
    }

    VERIFY(elf != nullptr);

    auto symbol = elf->find_symbol(node.address() - base_address);
    if (!symbol.has_value()) {
        dbgln("DisassemblyModel: symbol not found");
        return;
    }
    VERIFY(symbol.has_value());

    auto view = symbol.value().raw_data();

    X86::ELFSymbolProvider symbol_provider(*elf);
    X86::SimpleInstructionStream stream((const u8*)view.characters_without_null_termination(), view.length());
    X86::Disassembler disassembler(stream);

    size_t offset_into_symbol = 0;
    for (;;) {
        auto insn = disassembler.next();
        if (!insn.has_value())
            break;
        FlatPtr address_in_profiled_program = base_address + symbol.value().value() + offset_into_symbol;

        auto disassembly = insn.value().to_string(address_in_profiled_program, &symbol_provider);

        StringView instruction_bytes = view.substring_view(offset_into_symbol, insn.value().length());
        size_t samples_at_this_instruction = m_node.events_per_address().get(address_in_profiled_program).value_or(0);
        float percent = ((float)samples_at_this_instruction / (float)m_node.event_count()) * 100.0f;

        m_instructions.append({ insn.value(), disassembly, instruction_bytes, address_in_profiled_program, samples_at_this_instruction, percent });

        offset_into_symbol += insn.value().length();
    }
}

DisassemblyModel::~DisassemblyModel()
{
}

int DisassemblyModel::row_count(const GUI::ModelIndex&)  const
{
    return m_instructions.size();
}

String DisassemblyModel::column_name(int column)
{
    switch (column) {
    case Column::SampleCount:
        return m_profile.show_percentages() ? "% Samples" : "# Samples";
    case Column::Address:
        return "Address"


    }
}

}