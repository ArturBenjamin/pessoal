void delete_line(TextBuffer *buffer, int line)
{
    if (line < 0 || line >= buffer->num_lines)
        return;

    // 1. Libera a memória da linha
    free(buffer->lines[line]);

    // 2. Desloca todas as linhas abaixo para cima
    for (int i = line; i < buffer->num_lines - 1; i++)
    {
        buffer->lines[i] = buffer->lines[i + 1];
        buffer->line_lengths[i] = buffer->line_lengths[i + 1];
    }

    // 3. Reduz o número de linhas
    buffer->num_lines--;

    // 4. Se todas as linhas foram apagadas, cria uma linha vazia
    if (buffer->num_lines == 0)
    {
        buffer->num_lines = 1;
        buffer->lines = realloc(buffer->lines, sizeof(char *));
        buffer->line_lengths = realloc(buffer->line_lengths, sizeof(int));

        buffer->lines[0] = malloc(1);
        buffer->lines[0][0] = '\0';
        buffer->line_lengths[0] = 0;
    }
}
