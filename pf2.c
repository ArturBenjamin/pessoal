void paste_block(TextBuffer *buffer, int line_index, TextBuffer *clipboard)
{
    // 1. Verifica se há algo no clipboard
    if (clipboard == NULL || clipboard->num_lines == 0)
        return;

    // 2. Garante que o índice de inserção é válido
    if (line_index < 0)
        line_index = 0;
    if (line_index > buffer->num_lines)
        line_index = buffer->num_lines;

    // 3. Calcula o novo total de linhas
    int new_total = buffer->num_lines + clipboard->num_lines;

    // 4. Realoca memória para acomodar as novas linhas
    buffer->lines = realloc(buffer->lines, sizeof(char *) * new_total);
    buffer->line_lengths = realloc(buffer->line_lengths, sizeof(int) * new_total);

    // 5. Move as linhas abaixo do ponto de inserção para abrir espaço
    for (int i = buffer->num_lines - 1; i >= line_index; i--)
    {
        buffer->lines[i + clipboard->num_lines] = buffer->lines[i];
        buffer->line_lengths[i + clipboard->num_lines] = buffer->line_lengths[i];
    }

    // 6. Copia as linhas do clipboard para o buffer
    for (int i = 0; i < clipboard->num_lines; i++)
    {
        buffer->lines[line_index + i] = strdup(clipboard->lines[i]);
        buffer->line_lengths[line_index + i] = clipboard->line_lengths[i];
    }

    // 7. Atualiza o número total de linhas
    buffer->num_lines = new_total;
}
