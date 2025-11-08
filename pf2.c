void copy_block(TextBuffer *buffer, int start_line, int end_line, TextBuffer *clipboard)
{
    // Verifica limites válidos
    if (start_line < 0 || end_line >= buffer->num_lines || start_line > end_line)
        return;

    // Libera qualquer conteúdo anterior do clipboard
    for (int i = 0; i < clipboard->num_lines; i++)
        free(clipboard->lines[i]);
    free(clipboard->lines);
    free(clipboard->line_lengths);

    // Calcula o número de linhas que o bloco contém
    clipboard->num_lines = end_line - start_line + 1;

    // Aloca novas estruturas no clipboard
    clipboard->lines = malloc(sizeof(char *) * clipboard->num_lines);
    clipboard->line_lengths = malloc(sizeof(int) * clipboard->num_lines);

    // Copia linha por linha
    for (int i = 0; i < clipboard->num_lines; i++)
    {
        int src_index = start_line + i;
        clipboard->line_lengths[i] = buffer->line_lengths[src_index];
        clipboard->lines[i] = malloc(clipboard->line_lengths[i] + 1); // +1 para '\0'
        strcpy(clipboard->lines[i], buffer->lines[src_index]);
    }
}
