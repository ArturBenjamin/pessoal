int search_word(TextBuffer *buffer, const char *word, int *found_line, int *found_col)
{
    // 1. Verifica se há algo a procurar
    if (!buffer || !word || strlen(word) == 0)
        return 0; // nada a procurar

    // 2. Percorre cada linha do texto
    for (int i = 0; i < buffer->num_lines; i++)
    {
        char *pos = strstr(buffer->lines[i], word); // procura a palavra na linha

        // 3. Se encontrou, retorna linha e coluna
        if (pos != NULL)
        {
            *found_line = i;
            *found_col = (int)(pos - buffer->lines[i]);
            return 1; // encontrado!
        }
    }

    // 4. Caso chegue aqui, não achou
    return 0;
}
