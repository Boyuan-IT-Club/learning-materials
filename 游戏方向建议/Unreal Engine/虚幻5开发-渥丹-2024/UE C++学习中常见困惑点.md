# Unreal Engine 学习常见困惑点

## 1. BlueprintCallable 与 BlueprintNativeEvent 的区别

`BlueprintCallable` 和 `BlueprintNativeEvent` 是 Unreal Engine 中的两个不同的宏，它们都用于将 C++ 函数暴露给蓝图，但它们的使用场景和功能有所不同。

### `BlueprintCallable`

`BlueprintCallable` 用于在蓝图中调用 C++ 中的函数。使用 `BlueprintCallable` 的函数可以被蓝图脚本直接调用，就像调用其他蓝图节点一样。这允许蓝图开发者直接使用 C++ 提供的功能，而不需要了解 C++ 代码的实现细节。

**使用场景**：当你要在蓝图脚本中调用一个 C++ 函数，但不需要在蓝图脚本中重写这个函数时，使用 `BlueprintCallable`。

**特点**：

- 只能从蓝图调用。
- 通过 `BlueprintCallable` 暴露的函数不能被蓝图重写。

### `BlueprintNativeEvent`

`BlueprintNativeEvent` 用于在蓝图中重写 C++ 中的函数。使用 `BlueprintNativeEvent` 的函数可以同时在 C++ 和蓝图中实现，在蓝图中定义的实现会覆盖 C++ 中的默认实现。

**使用场景**：当你想在 C++ 中定义一个函数的默认行为，但是想在某些特殊的蓝图实例中重写这个函数的行为时，使用 `BlueprintNativeEvent`。

**特点**：

- 可以在 C++ 中定义函数的默认实现，然后在特定的蓝图中重写它。
- 通过 `BlueprintNativeEvent` 暴露的函数可以被蓝图重写。

### 总结

- `BlueprintCallable` 用来在蓝图中调用 C++ 函数，不支持在蓝图重写。
- `BlueprintNativeEvent` 用来在蓝图中重写 C++ 函数，允许在特定的蓝图中覆盖 C++ 的行为。

例如，如果你有一个 `PlayerController` 类，你想在游戏中进行一些功能定制，比如控制角色行为，你可以使用 `BlueprintNativeEvent` 来定义一个函数，然后在特定的玩家蓝图中重写这个函数。而如果你有一个计算功能比如射线检测，你可能只想在蓝图脚本中调用它而不需要在蓝图脚本中重写这个功能，这时你就会选择使用 `BlueprintCallable`。

## 2. AbilitySystemComponent，AbilitySystemComponentSpec和AbilitySystemComponentSpecHandle间的关系

`AbilitySystemComponent`、`AbilitySystemComponentSpec` 和 `AbilitySystemComponentSpecHandle` 是 Unreal Engine 中与能力系统（Ability System）相关的类，它们在管理和执行能力（Abilities）时各有其独特的作用。下面是它们之间的关系和功能解释：

### 1. `AbilitySystemComponent`

`AbilitySystemComponent` 是 Unreal Engine 的能力系统的核心组件，负责管理和处理角色的所有能力（Abilities）、状态效果（Effects）以及与能力相关的逻辑。它是角色或对象上持有能力系统的组件。

- **作用**：
  - 管理角色的能力、状态效果和资源。
  - 处理能力的激活、停止、冷却等逻辑。
  - 维护能力的相关数据，如能力的级别、持续时间、效果等。

- **常用功能**：
  - `GiveAbility`：给予一个能力给角色。
  - `RemoveAbility`：从角色上移除一个能力。
  - `TryActivateAbility`：尝试激活一个能力。

### 2. `AbilitySystemComponentSpec`

`AbilitySystemComponentSpec` 是能力系统中用来表示一个能力实例的结构体。它包含了有关能力的详细信息，如能力的特性、激活条件和效果等。这是能力系统内部用于管理和操作能力的一个重要数据结构。

- **作用**：
  - 封装了一个能力的所有相关数据。
  - 包含能力的配置、激活条件、效果和持续时间等。

- **常用功能**：
  - 可以通过 `AbilitySystemComponent` 创建和管理这些规格实例。
  - 在能力系统内部用于实际执行和处理能力逻辑。

### 3. `AbilitySystemComponentSpecHandle`

`AbilitySystemComponentSpecHandle` 是一个句柄，用于引用和管理 `AbilitySystemComponentSpec` 实例。它本质上是一个标识符，用来在能力系统中唯一标识一个 `AbilitySystemComponentSpec` 实例。

- **作用**：
  - 用于跟踪和管理能力规格实例的生命周期。
  - 通过句柄可以在能力系统中查找、更新或删除特定的能力规格实例。

- **常用功能**：
  - 通过句柄访问和操作对应的 `AbilitySystemComponentSpec` 实例。
  - 在能力的激活和执行过程中用于管理具体的能力实例。

### 它们之间的关系

1. **`AbilitySystemComponent`** 是整个能力系统的管理者和操作者，它处理与能力相关的所有逻辑。

2. 在 `AbilitySystemComponent` 内部，**`AbilitySystemComponentSpec`** 被用来表示具体的能力实例。每当一个能力被激活或创建时，`AbilitySystemComponent` 会生成一个 `AbilitySystemComponentSpec` 实例来管理这个能力的状态和效果。

3. **`AbilitySystemComponentSpecHandle`** 是一个指向 `AbilitySystemComponentSpec` 实例的引用。它用来标识和操作特定的 `AbilitySystemComponentSpec` 实例，使得能力系统能够在内部跟踪和管理能力的状态。

### 举例说明

假设你的角色在游戏中获得了一个新的能力：

1. 你会调用 `AbilitySystemComponent` 的 `GiveAbility` 方法来给予角色这个能力。

2. `AbilitySystemComponent` 会创建一个 `AbilitySystemComponentSpec` 实例，封装这个能力的所有信息和状态。

3. `AbilitySystemComponent` 会生成一个 `AbilitySystemComponentSpecHandle` 句柄来引用这个 `AbilitySystemComponentSpec` 实例。

4. 你可以通过这个句柄来管理和操作能力，比如检查能力的状态，或者在能力执行过程中更新能力规格的参数。

这样，`AbilitySystemComponent`、`AbilitySystemComponentSpec` 和 `AbilitySystemComponentSpecHandle` 共同协作，确保能力系统的各项功能能够顺利执行和管理。

> 1. Super
> 2. Cast<>()
> 3. Interface
> 4. override
> 5. DECLARE_MULTICAST_DELEGATE_OneParam与Broadcast
> 6. ATTRIBUTE_ACCESSORS
> 7. Blueprint Library
> 8. TSubclassOf<>
> 9. Montage
>10. AbilitySystemComponent，AbilitySystemComponentSpec和AbilitySystemComponentSpecHandle间的关系
>11. HasAuthority
