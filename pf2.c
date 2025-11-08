void cut_block(TextBuffer *buffer, int start_line, int end_line, TextBuffer *clipboard)
{
    // Verifica limites válidos
    if (start_line < 0 || end_line >= buffer->num_lines || start_line > end_line)
        return;

    // 1. Copia o bloco para o clipboard
    copy_block(buffer, start_line, end_line, clipboard);

    // 2. Calcula quantas linhas serão removidas
    int lines_to_remove = end_line - start_line + 1;

    // 3. Remove as linhas do buffer original
    for (int i = start_line; i <= end_line; i++)
        free(buffer->lines[i]); // libera memória das linhas cortadas

    // 4. Move as linhas restantes para "fechar o buraco"
    for (int i = end_line + 1; i < buffer->num_lines; i++)
    {
        buffer->lines[i - lines_to_remove] = buffer->lines[i];
        buffer->line_lengths[i - lines_to_remove] = buffer->line_lengths[i];
    }

    // 5. Atualiza o número total de linhas
    buffer->num_lines -= lines_to_remove;

    // 6. Reajusta a memória (opcional, mas boa prática)
    buffer->lines = realloc(buffer->lines, sizeof(char *) * buffer->num_lines);
    buffer->line_lengths = realloc(buffer->line_lengths, sizeof(int) * buffer->num_lines);
}
