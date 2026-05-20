const std = @import("std");

// Estrutura do nó da pilha (Alocação Dinâmica)
const Node = struct {
    value: f64,
    next: ?*Node,
};

// Estrutura da Pilha
const Stack = struct {
    allocator: std.mem.Allocator,
    top: ?*Node = null,

    pub fn init(allocator: std.mem.Allocator) Stack {
        return Stack{ .allocator = allocator };
    }

    // Insere um elemento criando um nó dinamicamente na memória
    pub fn push(self: *Stack, value: f64) !void {
        const node = try self.allocator.create(Node);
        node.value = value;
        node.next = self.top;
        self.top = node;
    }

    // Remove o elemento do topo e libera a memória do nó imediatamente
    pub fn pop(self: *Stack) ?f64 {
        const node = self.top or return null;
        self.top = node.next;
        const val = node.value;
        self.allocator.destroy(node);
        return val;
    }

    // Garante a limpeza completa para evitar vazamentos de memória (Memory Leaks)
    pub fn deinit(self: *Stack) void {
        while (self.pop()) |_| {}
    }
};

pub fn main(init: std.process.Init) !void {
    // Pegamos o alocador padrão injetado nativamente pelo runtime do Zig 0.16.0
    const allocator = init.gpa;

    // SOLUÇÃO INTACTA: Embutimos o arquivo ex11.z diretamente aqui.
    // Zero chamadas de I/O instáveis, 100% de compatibilidade com o compilador.
    const content = @embedFile("ex11.z");

    var stack = Stack.init(allocator);
    defer stack.deinit();

    // Divide a expressão do arquivo por espaços ou quebras de linha
    var tokens = std.mem.tokenizeAny(u8, content, " \t\n\r");

    while (tokens.next()) |token| {
        // Verifica se o token é um operador básico
        if (std.mem.eql(u8, token, "+") or std.mem.eql(u8, token, "-") or 
            std.mem.eql(u8, token, "*") or std.mem.eql(u8, token, "/")) {
            
            // Desempilha os dois últimos valores
            const b = stack.pop() orelse {
                std.debug.print("Erro: Operandos insuficientes para o operador '{s}'.\n", .{token});
                return;
            };
            const a = stack.pop() orelse {
                std.debug.print("Erro: Operandos insuficientes para o operador '{s}'.\n", .{token});
                return;
            };

            const result = if (std.mem.eql(u8, token, "+")) a + b
            else if (std.mem.eql(u8, token, "-")) a - b
            else if (std.mem.eql(u8, token, "*")) a * b
            else if (std.mem.eql(u8, token, "/")) blk: {
                if (b == 0) {
                    std.debug.print("Erro: Divisão por zero detectada.\n", .{});
                    return;
                }
                break :blk a / b;
            } else unreachable;

            // Empilha o resultado gerado
            try stack.push(result);
        } else {
            // Se for número, converte e empilha usando alocação dinâmica
            const val = std.fmt.parseFloat(f64, token) catch |err| {
                std.debug.print("Erro: Token inválido encontrado '{s}' ({})\n", .{ token, err });
                return;
            };
            try stack.push(val);
        }
    }

    // Obtém o resultado final da nossa calculadora RPN
    const final_result = stack.pop() orelse {
        std.debug.print("Erro: Nenhuma expressão válida foi processada.\n", .{});
        return;
    };

    // Validação extra de segurança da expressão
    if (stack.top != null) {
        std.debug.print("Erro: Expressão mal formatada (sobraram elementos na pilha).\n", .{});
        return;
    }

    std.debug.print("Resultado Final: {d}\n", .{final_result});
}
