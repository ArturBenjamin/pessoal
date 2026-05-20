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

    // Insere um elemento criando um nó dinamicamente na memória
    pub fn push(self: *Stack, value: f64) !void {
        const node = try self.allocator.create(Node);
        node.* = .{ .value = value, .next = self.top };
        self.top = node;
    }

    // Remove o elemento do topo e libera a memória do nó imediatamente
    pub fn pop(self: *Stack) ?f64 {
        const node = self.top orelse return null;
        self.top = node.next;
        const val = node.value;
        self.allocator.destroy(node); // Libera a memória
        return val;
    }

    // Limpeza completa para evitar vazamentos de memória
    pub fn deinit(self: *Stack) void {
        while (self.pop()) |_| {}
    }
};

pub fn main() !void {
    // USANDO O ALOCADOR QUE SABEMOS QUE FUNCIONA NO SEU ZIG
    const allocator = std.heap.page_allocator;

    // String direto no código para ignorar problemas de arquivo
    const content = "10 2 / 5 *";
    std.debug.print("Expressão a ser calculada: {s}\n", .{content});

    var stack = Stack.init(allocator);
    defer stack.deinit();

    var tokens = std.mem.tokenizeAny(u8, content, " \t\n\r");

    while (tokens.next()) |token| {
        if (std.mem.eql(u8, token, "+") or std.mem.eql(u8, token, "-") or 
            std.mem.eql(u8, token, "*") or std.mem.eql(u8, token, "/")) {
            
            const b = stack.pop() orelse return error.OperandosInsuficientes;
            const a = stack.pop() orelse return error.OperandosInsuficientes;

            const result = if (std.mem.eql(u8, token, "+")) a + b
            else if (std.mem.eql(u8, token, "-")) a - b
            else if (std.mem.eql(u8, token, "*")) a * b
            else if (std.mem.eql(u8, token, "/")) blk: {
                if (b == 0) return error.DivisaoPorZero;
                break :blk a / b;
            } else unreachable;

            try stack.push(result);
        } else {
            const val = try std.fmt.parseFloat(f64, token);
            try stack.push(val);
        }
    }

    if (stack.pop()) |final_result| {
        std.debug.print("Resultado Final: {d}\n", .{final_result});
    } else {
        std.debug.print("Erro: Pilha vazia no final da execução.\n", .{});
    }
}
