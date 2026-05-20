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
    const print = std.debug.print;

    // =========================================================
    // COMO TESTAR: Altere a expressão aqui dentro das aspas!
    // Exemplos: "10 2 / 5 *"  ou  "2 3 + 4 *"  ou  "15 5 /"
    // =========================================================
    const expressao = "10 2 / 5 *";
    
    print("----------------------------------------\n", .{});
    print("Expressao RPN recebida: {s}\n", .{expressao});
    print("----------------------------------------\n", .{});

    var stack = Stack.init(allocator);
    defer stack.deinit();

    var tokens = std.mem.tokenizeAny(u8, expressao, " \t\r\n");

    while (tokens.next()) |token| {
        if (std.mem.eql(u8, token, "+") or std.mem.eql(u8, token, "-") or 
            std.mem.eql(u8, token, "*") or std.mem.eql(u8, token, "/")) {
            
            const b = stack.pop() orelse {
                print("Erro: Faltam numeros para o operador '{s}'.\n", .{token});
                return;
            };
            const a = stack.pop() orelse {
                print("Erro: Faltam numeros para o operador '{s}'.\n", .{token});
                return;
            };

            const result = if (std.mem.eql(u8, token, "+")) a + b
            else if (std.mem.eql(u8, token, "-")) a - b
            else if (std.mem.eql(u8, token, "*")) a * b
            else if (std.mem.eql(u8, token, "/")) blk: {
                if (b == 0) {
                    print("Erro: Nao e possivel dividir por zero.\n", .{});
                    return;
                }
                break :blk a / b;
            } else unreachable;

            try stack.push(result);
        } else {
            // Se falhar ao tentar ler um numero, avisa o erro
            const val = std.fmt.parseFloat(f64, token) catch {
                print("Erro: Valor invalido detectado -> '{s}'\n", .{token});
                return;
            };
            try stack.push(val);
        }
    }

    if (stack.pop()) |final_result| {
        if (stack.top == null) {
            print("Resultado Final: {d}\n\n", .{final_result});
        } else {
            print("Erro: Sobraram numeros na pilha (conta incompleta).\n", .{});
        }
    } else {
        print("Nenhuma conta foi feita.\n", .{});
    }
}
