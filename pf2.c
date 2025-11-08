void delete_word(TextBuffer *buffer, int line, int col)
{
    if (line < 0 || line >= buffer->num_lines)
        return;

    char *txt = buffer->lines[line];
    int len = buffer->line_lengths[line];

    // 1. Se já estamos no fim da linha e existe linha abaixo → unir
    if (col >= len)
    {
        if (line < buffer->num_lines - 1)
            join_lines(buffer, line + 1);
        return;
    }

    int start = col;
    int end = col;

    // 2. Pular espaços iniciais (caso o cursor esteja entre palavras)
    while (end < len && (txt[end] == ' ' || txt[end] == '\t'))
        end++;

    // 3. Avançar até o final da palavra
    while (end < len && txt[end] != ' ' && txt[end] != '\t')
        end++;

    // 4. Remover os caracteres da palavra
    memmove(&txt[start], &txt[end], len - end + 1); // +1 inclui o '\0'
    buffer->line_lengths[line] -= (end - start);
}
