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
        return .{ .allocator = allocator };
    }

    pub fn push(self: *Stack, value: f64) !void {
        const node = try self.allocator.create(Node);
        node.* = .{ .value = value, .next = self.top };
        self.top = node;
    }

    pub fn pop(self: *Stack) ?f64 {
        const node = self.top orelse return null;
        self.top = node.next;
        const val = node.value;
        self.allocator.destroy(node); 
        return val;
    }

    pub fn deinit(self: *Stack) void {
        while (self.pop()) |_| {}
    }
};

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    
    // Pegamos as ferramentas de entrada (teclado) e saída (tela)
    const stdin = std.io.getStdIn().reader();
    const stdout = std.io.getStdOut().writer();

    // 1. Pede os valores ao usuário
    try stdout.print("Digite a expressao RPN (ex: 10 2 / 5 *): ", .{});

    // 2. Prepara um espaço na memória para guardar o que o usuário digitar
    var buffer: [1024]u8 = undefined;
    
    // 3. Lê o teclado até o usuário apertar Enter (\n)
    const input_or_null = try stdin.readUntilDelimiterOrEof(&buffer, '\n');

    if (input_or_null) |input| {
        var stack = Stack.init(allocator);
        defer stack.deinit();

        // Agora usamos o 'input' (o que você digitou) em vez de um texto fixo!
        var tokens = std.mem.tokenizeAny(u8, input, " \t\r");

        while (tokens.next()) |token| {
            if (std.mem.eql(u8, token, "+") or std.mem.eql(u8, token, "-") or 
                std.mem.eql(u8, token, "*") or std.mem.eql(u8, token, "/")) {
                
                const b = stack.pop() orelse {
                    try stdout.print("Erro: Faltam numeros para o operador '{s}'.\n", .{token});
                    return;
                };
                const a = stack.pop() orelse {
                    try stdout.print("Erro: Faltam numeros para o operador '{s}'.\n", .{token});
                    return;
                };

                const result = if (std.mem.eql(u8, token, "+")) a + b
                else if (std.mem.eql(u8, token, "-")) a - b
                else if (std.mem.eql(u8, token, "*")) a * b
                else if (std.mem.eql(u8, token, "/")) blk: {
                    if (b == 0) {
                        try stdout.print("Erro: Nao e possivel dividir por zero.\n", .{});
                        return;
                    }
                    break :blk a / b;
                } else unreachable;

                try stack.push(result);
            } else {
                const val = std.fmt.parseFloat(f64, token) catch {
                    try stdout.print("Erro: Valor invalido digitado -> '{s}'\n", .{token});
                    return;
                };
                try stack.push(val);
            }
        }

        if (stack.pop()) |final_result| {
            if (stack.top == null) {
                try stdout.print("Resultado Final: {d}\n", .{final_result});
            } else {
                try stdout.print("Erro: Sobraram numeros na pilha (conta incompleta).\n", .{});
            }
        } else {
            try stdout.print("Nenhuma conta foi feita.\n", .{});
        }
    } else {
        try stdout.print("\nNenhuma entrada detectada.\n", .{});
    }
}
